#include "n_chat.h"
#include "n_register.h"
#include "nettalk.h"
#include "ui_nettalk.h"
#include <QString>
#include <QPainter>
#include <QPixmap>
#include <QDesktopWidget>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QApplication>
#include "proto.h"

Nettalk::Nettalk(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Nettalk)
{
    ui->setupUi(this);

    sd = new QUdpSocket();

    QDesktopWidget *desktop = QApplication::desktop();
    this->setFixedSize(500, 360);
    this->setAutoFillBackground(true);
    this->setPalette(QPalette(Qt::white));
    this->move((desktop->width()-this->width())/2, (desktop->height()-this->height())/2);

    box1 = new QGroupBox(this);
    box2 = new QGroupBox(this);
    vBoxLayout = new QVBoxLayout();
    vBoxLayout2 = new QVBoxLayout();
    hBoxLayout = new QHBoxLayout();
    acLineEdit = new QLineEdit(box1);
    psLineEdit = new QLineEdit(box1);
    loginPushButton = new QPushButton("登录", box1);
    registerLabel = new QLabel("<style> a {text-decoration: none; color:#0099ff;} </style><a href='#'>注册账号</a>", box2);
    forgetLabel = new QLabel("<style> a {text-decoration: none; color:#0099ff} </style><a href='#'>忘记密码?</a>", box2);

    QFont ft("Microsoft YaHei", 12, 50, false);

    loginPushButton->setFont(ft);
    acLineEdit->setFont(ft);
    psLineEdit->setFont(ft);

    ft.setPixelSize(16);
    registerLabel->setFont(ft);
    forgetLabel->setFont(ft);

    acLineEdit->setEchoMode(QLineEdit::Normal);
    acLineEdit->setPlaceholderText("账号");
    psLineEdit->setEchoMode(QLineEdit::Password);
    psLineEdit->setPlaceholderText("密码");

    vBoxLayout->addWidget(acLineEdit);
    vBoxLayout->addWidget(psLineEdit);
    vBoxLayout->addWidget(loginPushButton);
    vBoxLayout->setSpacing(20);
    vBoxLayout->setContentsMargins(0, 0, 0, 0);
    box1->setLayout(vBoxLayout);

    hBoxLayout->addSpacerItem(new QSpacerItem(70, 0, QSizePolicy::Fixed));
    hBoxLayout->addWidget(registerLabel);
    hBoxLayout->setSpacing(50);
    hBoxLayout->addWidget(forgetLabel);
    hBoxLayout->setContentsMargins(0, 0, 0, 0);
    box2->setLayout(hBoxLayout);

    vBoxLayout2->addWidget(box1, 3);
    vBoxLayout2->addWidget(box2, 1);
    vBoxLayout2->setContentsMargins(0, 0, 0, 0);
    //vBoxLayout2->addSpacerItem(new QSpacerItem(0, 40, QSizePolicy::Expanding));
    this->setLayout(vBoxLayout2);

    box1->show();
    box2->show();
    acLineEdit->show();
    psLineEdit->show();
    registerLabel->show();
    forgetLabel->show();
    loginPushButton->show();
    this->setStyleSheet("\
    QGroupBox {width:80%; border:none; margin:10px 70px; padding-top:8px}\
    QLineEdit {border:1px solid #ccc; width:2000px; height:40px; border-radius:8px;padding-left:20px;}\
    QLineEdit:focus {border:1px solid #0099ff; width:200px; height:40px; border-radius:8px;}\
    QPushButton {background-color:#fff;border:2px solid #0099ff;\
                 color:#0099ff;width:80%;height:40px;margin:0 20px;\
                 border-radius: 8px;}\
    QPushButton:hover {background-color:#0099ff;border:1px solid #0099ff;\
                       color:#fff;width:80%;height:40px;margin:0 20px;\
                       border-radius: 8px;}\
    ");
    box2->setStyleSheet("height:20px;");

    connect(loginPushButton, SIGNAL(clicked(bool)), this, SLOT(loginPushButton_clicked()));
    connect(registerLabel, SIGNAL(linkActivated(QString)), this, SLOT(registerLabel_clicked()));
    connect(forgetLabel, SIGNAL(linkActivated(QString)), this, SLOT(forgetLabel_clicked()));
    connect(sd, SIGNAL(readyRead()), this, SLOT(sdRecv()));
}

Nettalk::~Nettalk()
{
    delete ui;
    delete box1;
    delete box2;
    delete sd;
}

void Nettalk::setAcLineEditText(QString str)
{
    this->acLineEdit->setText(str);
}

void Nettalk::loginPushButton_clicked()
{
    log_t login;
    memset(&login, '\0', sizeof(login));
    // 提取信息
    QString account = this->acLineEdit->text();
    QString passwd = this->psLineEdit->text();

    QByteArray pwd = passwd.toLatin1();
    pwd = QCryptographicHash::hash(pwd, QCryptographicHash::Sha512).toHex();

    snprintf(login.account, ACCSIZE, account.toStdString().c_str());
    snprintf(login.passwd, PWDSIZE, pwd.data());
    login.status = LOGIN;
    sd->writeDatagram((const char *)&login, sizeof(login), \
                      QHostAddress(QString(LOGIN_SERVER_IP)), LOGIN_SERVER_PORT);
    qDebug() << sd->localAddress() << sd->localPort();
}

void Nettalk::sdRecv()
{
    qDebug() << "nettalk";
    int ret;
    log_t login;
    N_chat *chat;
    sd->readDatagram((char *)&login, sizeof(login), NULL, NULL);
    qDebug() << "nettalk:sd:" << login.status;

    switch (login.status) {
    case LOGIN_STATUS_OK:
        chat = new N_chat(this->acLineEdit->text());
        chat->setAttribute(Qt::WA_DeleteOnClose);
        chat->setWindowTitle(this->acLineEdit->text());
        chat->show();
        this->close();
        break;
    case LOGIN_STATUS_ALREADY:
        ret = QMessageBox::warning(this, "登录", "请勿重复登录!", "我知道了");
        if (!ret) {
            this->acLineEdit->clear();
            this->psLineEdit->clear();
            acLineEdit->setEchoMode(QLineEdit::Normal);
            acLineEdit->setPlaceholderText("账号");
            psLineEdit->setEchoMode(QLineEdit::Password);
            psLineEdit->setPlaceholderText("密码");
        }
        break;
    case LOGIN_STATUS_ERROR:
        ret = QMessageBox::critical(this, "登录", "账号或密码有误!", "再试一次");
        if (!ret) {
            this->acLineEdit->clear();
            this->psLineEdit->clear();
            acLineEdit->setEchoMode(QLineEdit::Normal);
            acLineEdit->setPlaceholderText("账号");
            psLineEdit->setEchoMode(QLineEdit::Password);
            psLineEdit->setPlaceholderText("密码");
        }
        break;
    default:
        break;
    }

}

void Nettalk::registerLabel_clicked()
{
    N_register *reg = new N_register();
    reg->setWindowTitle("注册");
    reg->setAttribute(Qt::WA_DeleteOnClose);
    reg->show();
    this->close();
}

void Nettalk::forgetLabel_clicked()
{
    qDebug("forget\n");
}

//void Nettalk::paintEvent(QPaintEvent *event)
//{
//    QPainter painter(this);
//    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/new/prefix1/images/2.jpg"));
//}
