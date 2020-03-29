#ifndef N_CHAT_H
#define N_CHAT_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QTreeWidget>
#include <QTextEdit>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QToolBar>
#include <QGroupBox>
#include <QTextBrowser>
#include <QUdpSocket>

namespace Ui {
class N_chat;
}

class N_chat : public QWidget
{
    Q_OBJECT

public:
    explicit N_chat(QString mycnt, QWidget *parent = 0);
    ~N_chat();
    void closeEvent(QCloseEvent *event);

private slots:
    void friTreeWidget_clicked();
    void enterPushButton_clicked();
    void addFriPushButton_clicked();
    void sdRecv();
    void chatTextBrowserAutoScroll();

private:
    Ui::N_chat *ui;
    QGroupBox *boxFri;
    QGroupBox *boxChatTextEdit;
    QHBoxLayout *winBoxLayout;
    QHBoxLayout *inputLayout;
    QFrame *inputFrame;
    QVBoxLayout *friBoxLayout;
    QVBoxLayout *chatBoxLayout;
    QTreeWidget *friTreeWidget;
    QTextBrowser *chatTextBrowser;
    QTextEdit *inputTextEdit;
    QToolBar *toolBar;
    QPushButton *enterPushButton;
    QPushButton *addFriPushButton;
    QUdpSocket *sd;
    QString myaccount;
    QString fri_account;
};

#endif // N_CHAT_H
