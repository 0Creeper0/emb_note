#ifndef ADDFRIEND_H
#define ADDFRIEND_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QUdpSocket>

namespace Ui {
class AddFriend;
}

class AddFriend : public QWidget
{
    Q_OBJECT

public:
    explicit AddFriend(QUdpSocket *sd, QString mycnt, QWidget *parent = 0);
    ~AddFriend();

private slots:
    void commitPushButton_clicked();

private:
    Ui::AddFriend *ui;
    QGroupBox *box;
    QLineEdit *accountLineEdit;
    QPushButton *commitPushButton;
    QVBoxLayout *vBoxLayout;
    QHBoxLayout *hBoxLayout;
    QString myaccount;
    QUdpSocket *sd;
};

#endif // ADDFRIEND_H
