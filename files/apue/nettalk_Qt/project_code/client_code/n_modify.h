#ifndef N_MODIFY_H
#define N_MODIFY_H

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
class N_modify;
}

class N_modify : public QWidget
{
    Q_OBJECT

public:
    explicit N_modify(QWidget *parent = 0);
    ~N_modify();

private slots:
    void commitPushButton_clicked();
    void cancelPushButton_clicked();
    void sdRecv();


private:
    Ui::N_modify *ui;
    QGroupBox *box1;
    QGroupBox *box2;
    QLabel *accountLabel;
    QLabel *oldLabel;
    QLabel *passwdLabel;
    QLabel *passwd2Label;
    QLineEdit *accountLineEdit;
    QLineEdit *oldLineEdit;
    QLineEdit *passwdLineEdit;
    QLineEdit *passwd2LineEdit;
    QPushButton *commitPushButton;
    QPushButton *cancelPushButton;
    QGridLayout *gLayout;
    QHBoxLayout *hBoxLayout;
    QVBoxLayout *vBoxLayout;
    QUdpSocket *sd;
};

#endif // N_MODIFY_H
