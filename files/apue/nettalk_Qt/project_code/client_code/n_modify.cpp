#include "nettalk.h"
#include "n_modify.h"
#include "ui_n_modify.h"
#include <QDesktopWidget>
#include <QDebug>
#include <QCryptographicHash>
#include <QMessageBox>
#include "proto.h"

N_modify::N_modify(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::N_modify)
{
    ui->setupUi(this);

    sd = new QUdpSocket();

    QDesktopWidget *desktop = QApplication::desktop();
    this->setFixedSize(640, 400);
    this->move((desktop->width()-this->width())/2, (desktop->height()-this->height())/2);
    this->setAutoFillBackground(true);
    this->setPalette(QPalette(Qt::white));

    box1 = new QGroupBox(this);
    accountLabel = new QLabel("用户名", box1);
    oldLabel = new QLabel("原密码", box1);
    passwdLabel = new QLabel("新密码", box1);
    passwd2Label = new QLabel("确认密码", box1);
    accountLineEdit = new QLineEdit(box1);
    oldLineEdit = new QLineEdit(box1);
    passwdLineEdit = new QLineEdit(box1);
    passwd2LineEdit = new QLineEdit(box1);

    box2 = new QGroupBox(this);
    commitPushButton = new QPushButton("确定", box2);
    cancelPushButton = new QPushButton("取消", box2);

    gLayout = new QGridLayout(box1);
    hBoxLayout = new QHBoxLayout(box2);
    vBoxLayout = new QVBoxLayout(this);

    QFont ft("Microsoft YaHei", 12, 50, false);
    accountLabel->setFont(ft);
    oldLabel->setFont(ft);
    passwdLabel->setFont(ft);
    passwd2Label->setFont(ft);
    commitPushButton->setFont(ft);
    cancelPushButton->setFont(ft);
    accountLineEdit->setFont(ft);
    oldLineEdit->setFont(ft);
    passwdLineEdit->setFont(ft);
    passwd2LineEdit->setFont(ft);

    oldLineEdit->setEchoMode(QLineEdit::Password);
    passwdLineEdit->setEchoMode(QLineEdit::Password);
    passwd2LineEdit->setEchoMode(QLineEdit::Password);

    gLayout->addWidget(accountLabel, 0, 0, 1, 1, Qt::AlignRight);
    gLayout->addWidget(oldLabel, 1, 0, 1, 1, Qt::AlignRight);
    gLayout->addWidget(passwdLabel, 2, 0, 1, 1, Qt::AlignRight);
    gLayout->addWidget(passwd2Label, 3, 0, 1, 1, Qt::AlignRight);
    gLayout->addWidget(accountLineEdit, 0, 1, 1, 2);
    gLayout->addWidget(oldLineEdit, 1, 1, 1, 2);
    gLayout->addWidget(passwdLineEdit, 2, 1, 1, 2);
    gLayout->addWidget(passwd2LineEdit, 3, 1, 1, 2);
    gLayout->setSpacing(10);

    hBoxLayout->addWidget(commitPushButton);
    hBoxLayout->addWidget(cancelPushButton);
    hBoxLayout->setSpacing(30);

    vBoxLayout->addWidget(box1);
    vBoxLayout->addWidget(box2);

    box1->setLayout(gLayout);
    box2->setLayout(hBoxLayout);
    this->setLayout(vBoxLayout);

    box1->setObjectName(tr("box1"));

    box1->show();
    accountLabel->show();
    oldLabel->show();
    passwdLabel->show();
    passwd2Label->show();
    accountLineEdit->show();
    oldLineEdit->show();
    passwdLineEdit->show();
    passwd2LineEdit->show();
    box2->show();

    connect(commitPushButton, SIGNAL(clicked(bool)), this, SLOT(commitPushButton_clicked()));
    connect(cancelPushButton, SIGNAL(clicked(bool)), this, SLOT(cancelPushButton_clicked()));
    connect(sd, SIGNAL(readyRead()), this, SLOT(sdRecv()));

    this->setStyleSheet("\
    QGroupBox {width:300px; border:0px; margin:10px 30px; padding-top:8px;}\
    #box1 {width:300px; border:0px; margin:10px 30px; padding-top:8px; padding-right:80px;}\
    QLineEdit {border:1px solid #ccc; width:200px; height:40px; border-radius:8px;padding-left:20px;}\
    QLineEdit:focus {border:1px solid #0099ff; width:200px; height:40px; border-radius:8px;}\
    QPushButton {background-color:#fff;border:2px solid #0099ff;\
                 color:#0099ff;width:80%;height:30px;margin:0 20px;\
                 border-radius: 8px;}\
    QPushButton:hover {background-color:#0099ff;border:1px solid #0099ff;\
                       color:#fff;width:80%;height:30px;margin:0 20px;\
                       border-radius: 8px;}\
    ");

}

N_modify::~N_modify()
{
    delete ui;
    delete box1;
    delete box2;
    delete vBoxLayout;
    delete sd;
}

void N_modify::commitPushButton_clicked()
{
    QString account = this->accountLineEdit->text();
    QString oldpasswd = this->oldLineEdit->text();
    QString passwd = this->passwdLineEdit->text();
    QString passwd2 = this->passwd2LineEdit->text();
    if(account.length() == 0) {
        this->accountLineEdit->setStyleSheet("border:1px solid red");
        this->accountLineEdit->clear();
        this->accountLineEdit->setPlaceholderText("请输入账号");
    } else {
        // 密码验证
        this->accountLineEdit->setStyleSheet("border:1px solid #ccc");
        if(oldpasswd.length() < 6) {
            this->oldLineEdit->setStyleSheet("border:1px solid red");
            this->oldLineEdit->clear();
            this->oldLineEdit->setPlaceholderText("请检查原密码");
        } else if(oldpasswd == passwd) {
            this->oldLineEdit->setStyleSheet("border:1px solid #ccc");
            this->passwdLineEdit->setStyleSheet("border:1px solid red");
            this->passwdLineEdit->clear();
            this->passwdLineEdit->setPlaceholderText("新密码不能与原密码一致");
        } else if(passwd.length() < 6) {
            this->passwdLineEdit->setStyleSheet("border:1px solid red");
            this->passwd2LineEdit->setStyleSheet("border:1px solid red");
            this->passwdLineEdit->clear();
            this->passwd2LineEdit->clear();
            this->passwdLineEdit->setPlaceholderText("密码至少6位");
            this->passwd2LineEdit->setPlaceholderText("请重新输入");
        } else {
            if(passwd != passwd2) {
                qDebug() << "no";
                this->passwdLineEdit->setStyleSheet("border:1px solid red");
                this->passwd2LineEdit->setStyleSheet("border:1px solid red");
                this->passwdLineEdit->clear();
                this->passwd2LineEdit->clear();
                this->passwdLineEdit->setPlaceholderText("两次密码不一样");
                this->passwd2LineEdit->setPlaceholderText("请重新输入");
            } else {
                this->oldLineEdit->setStyleSheet("border:1px solid #ccc");
                this->passwdLineEdit->setStyleSheet("border:1px solid #ccc");
                this->passwd2LineEdit->setStyleSheet("border:1px solid #ccc");
                // 信息格式正确 可以发包
                mod_t mod;
                memset(&mod, '\0', sizeof(mod));
                snprintf(mod.account, ACCSIZE, account.toStdString().c_str());
                memset(&mod.email, '\0', EMAILSIZE);
                memset(&mod.phone, '\0', PHONESIZE);


                // 密码进行Sha加密
                QByteArray pwd = oldpasswd.toLatin1();
                pwd = QCryptographicHash::hash(pwd, QCryptographicHash::Sha512).toHex();
                snprintf(mod.old_passwd, OLDPWDSIZE, pwd.toStdString().c_str());

                pwd = passwd.toLatin1();
                pwd = QCryptographicHash::hash(pwd, QCryptographicHash::Sha512).toHex();
                snprintf(mod.passwd, PWDSIZE, pwd.toStdString().c_str());

                mod.status = MOD_STATUS_OK;
                // 发送
                sd->writeDatagram((const char *)&mod, sizeof(mod), \
                                  QHostAddress(QString(MOD_SERVER_IP)), MOD_SERVER_PORT);
                qDebug() << mod.account << mod.old_passwd << mod.passwd << mod.status;
            }
        }
    }
}

void N_modify::cancelPushButton_clicked()
{
    Nettalk *nt = new Nettalk();
    nt->setAttribute(Qt::WA_DeleteOnClose);
    nt->show();
    this->close();
}

void N_modify::sdRecv()
{
    // 收到服务端的包
    mod_t mod;
    int ret;
    sd->readDatagram((char *)&mod, sizeof(mod), NULL, NULL);
    switch (mod.status) {
    case MOD_STATUS_OK:
        ret = QMessageBox::information(this, "修改密码", "恭喜!\n修改成功 请登录!", "确定");
        if (!ret) {
            Nettalk *nt = new Nettalk();
            nt->setAttribute(Qt::WA_DeleteOnClose);
            nt->show();
            nt->setAcLineEditText(this->accountLineEdit->text());
            this->close();
        }
        break;
    case MOD_STATUS_ERROR:
        ret = QMessageBox::question(this, "修改密码", "账号密码错误或服务器异常!\n是否重新修改?", \
                       "是", "否");
        if(ret == 0) {
            this->accountLineEdit->clear();
            this->oldLineEdit->clear();
            this->passwdLineEdit->clear();
            this->passwd2LineEdit->clear();
        } else if (ret == 1) {
            Nettalk *nt = new Nettalk();
            nt->setAttribute(Qt::WA_DeleteOnClose);
            nt->show();
            this->close();
        }
        break;
    default:
        break;
    }
}
