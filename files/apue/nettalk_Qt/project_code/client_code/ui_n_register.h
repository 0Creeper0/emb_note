/********************************************************************************
** Form generated from reading UI file 'n_register.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_N_REGISTER_H
#define UI_N_REGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_N_register
{
public:

    void setupUi(QWidget *N_register)
    {
        if (N_register->objectName().isEmpty())
            N_register->setObjectName(QStringLiteral("N_register"));
        N_register->resize(400, 300);

        retranslateUi(N_register);

        QMetaObject::connectSlotsByName(N_register);
    } // setupUi

    void retranslateUi(QWidget *N_register)
    {
        N_register->setWindowTitle(QApplication::translate("N_register", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class N_register: public Ui_N_register {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_N_REGISTER_H
