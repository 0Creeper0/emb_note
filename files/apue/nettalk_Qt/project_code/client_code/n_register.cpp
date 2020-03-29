#include "nettalk.h"
#include "n_register.h"
#include "ui_n_register.h"
#include <QDesktopWidget>
#include <QDebug>
#include <QCryptographicHash>
#include <QMessageBox>
#include "proto.h"

N_register::N_register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::N_register)
{
    ui->setupUi(this);

    sd = new QUdpSocket();

    qDebug() << sd->localAddress() << sd->localPort();

    QDesktopWidget *desktop = QApplication::desktop();
    this->setFixedSize(640, 400);
    this->move((desktop->width()-this->width())/2, (desktop->height()-this->height())/2);
    this->setAutoFillBackground(true);
    this->setPalette(QPalette(Qt::white));

    box1 = new QGroupBox(this);
    accountLabel = new QLabel("用户名", box1);
    passwdLabel = new QLabel("密码", box1);
    passwd2Label = new QLabel("确认密码", box1);
    emailLabel = new QLabel("邮箱", box1);
    phoneLabel = new QLabel("手机号", box1);
    accountLineEdit = new QLineEdit(box1);
    passwdLineEdit = new QLineEdit(box1);
    passwd2LineEdit = new QLineEdit(box1);
    emailLineEdit = new QLineEdit(box1);
    phoneLineEdit = new QLineEdit(box1);

    box2 = new QGroupBox(this);
    commitPushButton = new QPushButton("确定", box2);
    cancelPushButton = new QPushButton("取消", box2);

    gLayout = new QGridLayout(box1);
    hBoxLayout = new QHBoxLayout(box2);
    vBoxLayout = new QVBoxLayout(this);

    QFont ft("Microsoft YaHei", 12, 50, false);
    accountLabel->setFont(ft);
    passwdLabel->setFont(ft);
    passwd2Label->setFont(ft);
    emailLabel->setFont(ft);
    phoneLabel->setFont(ft);
    commitPushButton->setFont(ft);
    cancelPushButton->setFont(ft);
    accountLineEdit->setFont(ft);
    emailLineEdit->setFont(ft);
    phoneLineEdit->setFont(ft);

    passwdLineEdit->setEchoMode(QLineEdit::Password);
    passwd2LineEdit->setEchoMode(QLineEdit::Password);

    gLayout->addWidget(accountLabel, 0, 0, 1, 1, Qt::AlignRight);
    gLayout->addWidget(passwdLabel, 1, 0, 1, 1, Qt::AlignRight);
    gLayout->addWidget(passwd2Label, 2, 0, 1, 1, Qt::AlignRight);
    gLayout->addWidget(emailLabel, 3, 0, 1, 1, Qt::AlignRight);
    gLayout->addWidget(phoneLabel, 4, 0, 1, 1, Qt::AlignRight);
    gLayout->addWidget(accountLineEdit, 0, 1, 1, 2);
    gLayout->addWidget(passwdLineEdit, 1, 1, 1, 2);
    gLayout->addWidget(passwd2LineEdit, 2, 1, 1, 2);
    gLayout->addWidget(emailLineEdit, 3, 1, 1, 2);
    gLayout->addWidget(phoneLineEdit, 4, 1, 1, 2);
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
    passwdLabel->show();
    passwd2Label->show();
    emailLabel->show();
    phoneLabel->show();
    accountLineEdit->show();
    passwdLineEdit->show();
    passwd2LineEdit->show();
    emailLineEdit->show();
    phoneLineEdit->show();
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

N_register::~N_register()
{
    // 只销毁父组件即可, c++内存管理机制会自动销毁子组件
    delete ui;
    delete box1;
    delete box2;
    delete vBoxLayout;
    delete sd;
}

void N_register::commitPushButton_clicked()
{
    QString account = this->accountLineEdit->text();
    QString passwd = this->passwdLineEdit->text();
    QString passwd2 = this->passwd2LineEdit->text();
    QString email = this->emailLineEdit->text();
    QString phone = this->phoneLineEdit->text();

    if(account.length() > 20) {
        // 账号验证
        this->accountLineEdit->setStyleSheet("border:1px solid red");
        this->accountLineEdit->clear();
        this->accountLineEdit->setPlaceholderText("账号过长");
    } else if(account.length() == 0) {
        this->accountLineEdit->setStyleSheet("border:1px solid red");
        this->accountLineEdit->clear();
        this->accountLineEdit->setPlaceholderText("请输入账号");
    } else {
        // 密码验证
        this->accountLineEdit->setStyleSheet("border:1px solid #ccc");
        if(passwd.length() < 6) {
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
                this->passwdLineEdit->setStyleSheet("border:1px solid #ccc");
                this->passwd2LineEdit->setStyleSheet("border:1px solid #ccc");
                // 验证邮箱 正则判断
                QString pattern("\\w+@\\w+\\.\\w+");    /*qt中正则用转义时要输入两个\   */
                QRegExp rx(pattern);
                if(!rx.exactMatch(email)) {
                    this->emailLineEdit->setStyleSheet("border:1px solid red");
                    this->emailLineEdit->clear();
                    this->emailLineEdit->setPlaceholderText("邮箱格式不符合");
                } else {
                    this->emailLineEdit->setStyleSheet("border:1px solid #ccc");
                    // 验证手机号
                    if(phone.length() != 11) {
                        this->phoneLineEdit->setStyleSheet("border:1px solid red");
                        this->phoneLineEdit->clear();
                        this->phoneLineEdit->setPlaceholderText("手机号位数有误");
                    } else {
                        this->phoneLineEdit->setStyleSheet("border:1px solid #ccc");
                        // 信息格式正确 可以发包
                        reg_t reg;
                        memset(&reg, '\0', sizeof(reg));
                        snprintf(reg.account, ACCSIZE, account.toStdString().c_str());
                        snprintf(reg.email, EMAILSIZE, email.toStdString().c_str());
                        snprintf(reg.phone, PHONESIZE, phone.toStdString().c_str());

                        // 密码进行Sha加密
                        QByteArray pwd = passwd.toLatin1();
                        pwd = QCryptographicHash::hash(pwd, QCryptographicHash::Sha512).toHex();
                        snprintf(reg.passwd, PWDSIZE, pwd.data());

                        // 发送
                        sd->writeDatagram((const char *)&reg, sizeof(reg), \
                                          QHostAddress(QString(REG_SERVER_IP)), REG_SERVER_PORT);
                        qDebug() << REG_SERVER_IP << REG_SERVER_PORT;
                    }
                }
            }
        }
    }


}

void N_register::cancelPushButton_clicked()
{
    Nettalk *nt = new Nettalk();
    nt->setAttribute(Qt::WA_DeleteOnClose);
    nt->show();
    this->close();
}

void N_register::sdRecv()
{
    // 收到服务端的包
    reg_t reg;
    int ret;
    sd->readDatagram((char *)&reg, sizeof(reg), NULL, NULL);
    switch (reg.status) {
    case REG_STATUS_OK:
        ret = QMessageBox::information(this, "注册", "恭喜!\n注册成功 请登录!", "确定");
        if (!ret) {
            Nettalk *nt = new Nettalk();
            nt->setAttribute(Qt::WA_DeleteOnClose);
            nt->show();
            nt->setAcLineEditText(this->accountLineEdit->text());
            this->close();
        }
        break;
    case REG_STATUS_ALREADY:
        ret = QMessageBox::question(this, "注册", "账号已经存在!\n是否重新注册?", \
                       "是", "否");
        if(ret == 0) {
            this->accountLineEdit->clear();
            this->accountLineEdit->setStyleSheet("border:1px solid red");
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
