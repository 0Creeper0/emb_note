#include <iostream>
#include "nettalk.h"
#include "addfriend.h"
#include "n_chat.h"
#include "ui_n_chat.h"
#include <QString>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QCloseEvent>
#include <QHostAddress>
#include <QDateTime>
#include "proto.h"

N_chat::N_chat(QString mycnt, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::N_chat)
{
    ui->setupUi(this);

    chat_t chat;
    myaccount = mycnt;
    fri_account = myaccount;

    snprintf(chat.account, ACCSIZE, myaccount.toStdString().c_str());
    chat.status = CHAT_STATUS_SHOW;
    sd = new QUdpSocket();
    this->sd->writeDatagram((char *)&chat, sizeof(chat), \
                      QHostAddress(QString(CHAT_SERVER_IP)), CHAT_SERVER_PORT);
    qDebug() << this->sd->localAddress() << this->sd->localPort();

    // 居中窗口 设置大小
    QDesktopWidget *desktop = QApplication::desktop();
    this->resize(1024, 768);
    this->move((desktop->width()-this->width())/2, (desktop->height()-this->height())/2);
    this->setWindowTitle("");
    this->setAutoFillBackground(true);
    this->setPalette(QPalette(Qt::white));

    QFont ft("Microsoft YaHei", 10, 50, false);

    // 好友列表
    boxFri = new QGroupBox(this);
    friTreeWidget = new QTreeWidget(boxFri);
    friTreeWidget->setHeaderLabel(tr("我的好友"));
    addFriPushButton = new QPushButton("添加好友",boxFri);
    addFriPushButton->setObjectName(tr("addbtn"));

    // 聊天区域
    boxChatTextEdit = new QGroupBox(this);
    chatTextBrowser = new QTextBrowser(boxChatTextEdit);
    inputFrame = new QFrame(boxChatTextEdit);
    inputFrame->setObjectName(tr("inpframe"));
    inputTextEdit = new QTextEdit(inputFrame);
    inputTextEdit->setObjectName(tr("inptextedit"));
    inputTextEdit->setDisabled(true);
    toolBar = new QToolBar(boxChatTextEdit);
    enterPushButton = new QPushButton("发送", inputFrame);
    //enterPushButton->setGeometry(this->width()-200, this->height()-100, 150, 40);
    //enterPushButton->setLayout(btnLayout);
    //enterPushButton->raise();

    addFriPushButton->setFont(ft);
    enterPushButton->setFont(ft);

    // toolbar
    QAction *action = new QAction("", NULL);
    action->setToolTip("emoji");
    action->setIcon(QIcon(":/new/prefix1/images/emoji2.svg"));
    toolBar->addAction(action);

    // 窗口布局
    friBoxLayout = new QVBoxLayout(this);
    friBoxLayout->addWidget(friTreeWidget, 10);
    friBoxLayout->addWidget(addFriPushButton, 1);
    friBoxLayout->setContentsMargins(0, 0, 0, 0);
    boxFri->setLayout(friBoxLayout);
    boxFri->setObjectName("box");

    chatBoxLayout = new QVBoxLayout(this);
    chatBoxLayout->addWidget(chatTextBrowser, 6);
    chatBoxLayout->addWidget(toolBar, 1);
    chatBoxLayout->addWidget(inputFrame, 2);
    chatBoxLayout->setContentsMargins(0, 0, 0, 0);
    boxChatTextEdit->setLayout(chatBoxLayout);
    inputLayout = new QHBoxLayout(inputFrame);
    inputLayout->addWidget(inputTextEdit, 5);
    inputLayout->addWidget(enterPushButton, 1);
    inputLayout->setContentsMargins(0, 0, 0, 0);
    inputFrame->setLayout(inputLayout);


    winBoxLayout = new QHBoxLayout(this);
    winBoxLayout->addWidget(boxFri, 1);
    winBoxLayout->addWidget(boxChatTextEdit, 3);
    winBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(winBoxLayout);

    toolBar->show();
    boxFri->show();
    boxChatTextEdit->show();
    friTreeWidget->show();
    chatTextBrowser->show();
    inputTextEdit->show();

    this->setStyleSheet("\
    QTextEdit {width:100%;border:1px solid #0099ff;}\
    QToolBar {border:1px solid #0099ff; width:100%; height:27px; max-height:27px;\
    min-height:27px; background-color:#fff; border-radius: 8px;}\
    QGroupBox {border:3px solid #0099ff; margin:0px; padding:0px; border-radius: 8px;}\
    #inpframe {border:1px solid #0099ff;}\
    #inptextedit {border:none;}\
    QTreeWidget {border:1px solid #0099ff;}\
    QPushButton {background-color:#fff;border:2px solid #0099ff;\
                 color:#0099ff; width:100%; height:30%; margin:0 20px;\
                 border-radius: 8px;}\
    QPushButton:hover {background-color:#0099ff;border:1px solid #0099ff;\
                       color:#fff;margin:0 20px;\
                       border-radius: 8px;}\
    #addbtn {color:#000; border:1px solid #0099ff; margin:0; border-radius:0px}\
    #addbtn:hover {color:#fff; border:1px solid #0099ff; margin:0; border-radius:0px}");


    // 槽函数
    connect(friTreeWidget, SIGNAL(clicked(QModelIndex)), this, SLOT(friTreeWidget_clicked()));
    connect(enterPushButton, SIGNAL(clicked(bool)), this, SLOT(enterPushButton_clicked()));
    connect(addFriPushButton, SIGNAL(clicked(bool)), this, SLOT(addFriPushButton_clicked()));
    connect(this->sd, SIGNAL(readyRead()), this, SLOT(sdRecv()));
    connect(this->chatTextBrowser, SIGNAL(textChanged()), this, SLOT(chatTextBrowserAutoScroll()));
}

N_chat::~N_chat()
{
    delete ui;
    delete inputFrame;
    delete boxChatTextEdit;
    delete boxFri;
    delete sd;
}

void N_chat::closeEvent(QCloseEvent *event)
{
    // 窗口关闭
    log_t logout;
    snprintf(logout.account, ACCSIZE, this->myaccount.toStdString().c_str());
    logout.status = LOGOUT;
    int ret = QMessageBox::question(this, "退出", "真的要退出吗?", \
                                    "退出", "再想想");
    switch (ret) {
    case 0:
        //event
        event->accept();
        sd->writeDatagram((char *)&logout, sizeof(logout), \
                          QHostAddress(QString(LOGIN_SERVER_IP)), LOGIN_SERVER_PORT);
        break;
    case 1:
        event->ignore();
        break;
    default:
        break;
    }
}

void N_chat::friTreeWidget_clicked()
{
    this->inputTextEdit->setEnabled(true);
    QTreeWidgetItem *cur = friTreeWidget->currentItem();
    if (this->fri_account != cur->text(0)) {
        this->fri_account = cur->text(0); // 当前聊天好友
        this->setWindowTitle(tr("与")+this->fri_account+tr("的聊天/*- ")+this->myaccount+tr(" -*/"));
        this->chatTextBrowser->clear();
    }
}

void N_chat::enterPushButton_clicked()
{
    chat_t chat;
    QString inputStr = inputTextEdit->toPlainText();
    if (this->myaccount != this->fri_account) {
        chatTextBrowser->insertHtml(tr("<p>")+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm")+\
                                tr("</p>")+tr("<p><font color='blue'>")+inputStr+tr("</font></p><br>"));
    }
    inputTextEdit->clear();

    snprintf(chat.account, ACCSIZE, myaccount.toStdString().c_str());
    snprintf(chat.fri_account, FRISIZE, fri_account.toStdString().c_str());
    snprintf(chat.msg, MSGSIZE, inputStr.toStdString().c_str());
    chat.status = CHAT_STATUS_CHAT;
    qDebug() << chat.account << chat.fri_account;

    sd->writeDatagram((const char *)&chat, sizeof(chat), \
                      QHostAddress(QString(CHAT_SERVER_IP)), CHAT_SERVER_PORT);
}

void N_chat::addFriPushButton_clicked()
{
    AddFriend *ad = new AddFriend(sd, this->myaccount);
    qDebug() << "toadd:" << sd->localAddress() <<sd->localPort();
    ad->setWindowTitle(tr("添加好友"));
    ad->show();
}

void N_chat::sdRecv()
{
    qDebug() << "chat";
    int ret;
    QTreeWidgetItem *fri;
    QString fri_account;
    chat_t chat;
    sd->readDatagram((char *)&chat, sizeof(chat), NULL, NULL);
    qDebug() << "add:" << sd->localAddress() <<sd->localPort() << chat.status;
    switch (chat.status) {
    case SHOW_STATUS_OK:
        fri_account = QString(chat.fri_account);
        fri = new QTreeWidgetItem(friTreeWidget, QStringList(fri_account));
        break;
    case SHOW_STATUS_ERROR:
        ret = QMessageBox::warning(this, "警告", "获取好友列表出错!", "我知道了");
        break;
    case ADD_STATUS_OK:
        fri_account = QString(chat.fri_account);
        fri = new QTreeWidgetItem(friTreeWidget, QStringList(fri_account));
        break;
    case ADD_STATUS_ALREADY:
        ret = QMessageBox::warning(this, "警告", "对方已是您的好友 无需添加!", "我知道了");
        break;
    case ADD_STATUS_ERROR:
        ret = QMessageBox::critical(this, "错误", "添加好友失败 请重试!", "我知道了");
        break;
    case CHAT_STATUS_CHAT:
        this->chatTextBrowser->insertHtml(tr("<p>")+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm")+\
                                tr("</p>")+tr("<p><font color='blue'>")+QString(chat.msg)+tr("</font></p><br>"));
        break;
    case MSG_STATUS_OK:
        qDebug() << "send ok";
        break;
    case MSG_STATUS_ERROR:
        qDebug() << "send err";
        ret = QMessageBox::warning(this, "警告", "对方不在线!", "我知道了");
        break;
    default:
        break;
    }
}

void N_chat::chatTextBrowserAutoScroll()
{
    this->chatTextBrowser->moveCursor(QTextCursor::End);
}
