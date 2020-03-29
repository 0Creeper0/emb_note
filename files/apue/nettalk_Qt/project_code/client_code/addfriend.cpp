#include "addfriend.h"
#include "ui_addfriend.h"
#include <QDesktopWidget>
#include "proto.h"

AddFriend::AddFriend(QUdpSocket *sd, QString mycnt, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddFriend)
{
    ui->setupUi(this);

    myaccount = mycnt;

    this->sd = sd;
    qDebug() << this->sd->localAddress() << this->sd->localPort();

    // 居中窗口 设置大小
    QDesktopWidget *desktop = QApplication::desktop();
    this->setFixedSize(640, 400);
    this->move((desktop->width()-this->width())/2, (desktop->height()-this->height())/2);
    this->setAutoFillBackground(true);
    this->setPalette(QPalette(Qt::white));

    QFont ft("Microsoft YaHei", 10, 50, false);

    box = new QGroupBox(this);
    accountLineEdit = new QLineEdit(box);
    accountLineEdit->setPlaceholderText("添加好友账号");
    commitPushButton = new QPushButton("确认", box);

    accountLineEdit->setFont(ft);
    commitPushButton->setFont(ft);

    // 布局

    vBoxLayout = new QVBoxLayout(box);
    vBoxLayout->addWidget(accountLineEdit);
    vBoxLayout->addWidget(commitPushButton);
    box->setLayout(vBoxLayout);

    hBoxLayout = new QHBoxLayout(this);
    hBoxLayout->addSpacing(90);
    hBoxLayout->addWidget(box);
    hBoxLayout->addSpacing(90);
    this->setLayout(hBoxLayout);

    box->show();
    accountLineEdit->show();
    commitPushButton->show();
    this->show();
    this->setStyleSheet("\
    QGroupBox {width:300px; border:none; margin:10px 30px; padding-top:8px}\
    QLineEdit {border:1px solid #ccc; width:200px; height:40px; border-radius:8px;padding-left:20px;}\
    QLineEdit:focus {border:1px solid #0099ff; width:200px; height:40px; border-radius:8px;}\
    QPushButton {background-color:#fff;border:2px solid #0099ff;\
                 color:#0099ff;width:60%;height:35px;margin:0 20px;\
                 border-radius: 8px;}\
    QPushButton:hover {background-color:#0099ff;border:1px solid #0099ff;\
                       color:#fff;width:60%;height:35px;margin:0 20px;\
                       border-radius: 8px;}\
    ");

    connect(commitPushButton, SIGNAL(clicked(bool)), this, SLOT(commitPushButton_clicked()));
}

AddFriend::~AddFriend()
{
    delete ui;
    delete box;
    delete hBoxLayout;
}

void AddFriend::commitPushButton_clicked()
{
    chat_t chat;
    QString fri_account = this->accountLineEdit->text();
    snprintf(chat.account, ACCSIZE, this->myaccount.toStdString().c_str());
    snprintf(chat.fri_account, FRISIZE, fri_account.toStdString().c_str());
    chat.status = CHAT_STATUS_ADD;
    this->sd->writeDatagram((char *)&chat, sizeof(chat), \
                            QHostAddress(QString(CHAT_SERVER_IP)), CHAT_SERVER_PORT);
    this->close();

}
