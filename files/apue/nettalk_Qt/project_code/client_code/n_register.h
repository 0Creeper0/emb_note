#ifndef N_REGISTER_H
#define N_REGISTER_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QUdpSocket>

namespace Ui {
class N_register;
}

class N_register : public QWidget
{
    Q_OBJECT

public:
    explicit N_register(QWidget *parent = 0);
    ~N_register();

private slots:
    void commitPushButton_clicked();
    void cancelPushButton_clicked();
    void sdRecv();

private:
    Ui::N_register *ui;
    QGroupBox *box1;
    QGroupBox *box2;
    QLabel *accountLabel;
    QLabel *passwdLabel;
    QLabel *passwd2Label;
    QLabel *emailLabel;
    QLabel *phoneLabel;
    QLineEdit *accountLineEdit;
    QLineEdit *passwdLineEdit;
    QLineEdit *passwd2LineEdit;
    QLineEdit *emailLineEdit;
    QLineEdit *phoneLineEdit;
    QPushButton *commitPushButton;
    QPushButton *cancelPushButton;
    QGridLayout *gLayout;
    QHBoxLayout *hBoxLayout;
    QVBoxLayout *vBoxLayout;
    QUdpSocket *sd;
};

#endif // N_REGISTER_H
