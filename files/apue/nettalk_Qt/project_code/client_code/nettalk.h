#ifndef NETTALK_H
#define NETTALK_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QPushButton>
#include <QUdpSocket>


namespace Ui {
class Nettalk;
}

class Nettalk : public QDialog
{
    Q_OBJECT

public:
    explicit Nettalk(QWidget *parent = 0);
    ~Nettalk();
    void setAcLineEditText(QString str);

private slots:
    void registerLabel_clicked();
    void modLabel_clicked();
    void loginPushButton_clicked();
    void sdRecv();

//private:
//    void paintEvent(QPaintEvent *event);

private:
    Ui::Nettalk *ui;
    QGroupBox *box1;
    QGroupBox *box2;
    QLineEdit *acLineEdit;
    QLineEdit *psLineEdit;
    QPushButton *loginPushButton;
    QVBoxLayout *vBoxLayout;
    QVBoxLayout *vBoxLayout2;
    QHBoxLayout *hBoxLayout;
    QLabel *registerLabel;
    QLabel *modLabel;
    QUdpSocket *sd;
};

#endif // NETTALK_H
