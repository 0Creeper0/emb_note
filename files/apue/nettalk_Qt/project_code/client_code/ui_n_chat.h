/********************************************************************************
** Form generated from reading UI file 'n_chat.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_N_CHAT_H
#define UI_N_CHAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_N_chat
{
public:

    void setupUi(QWidget *N_chat)
    {
        if (N_chat->objectName().isEmpty())
            N_chat->setObjectName(QStringLiteral("N_chat"));
        N_chat->resize(400, 300);

        retranslateUi(N_chat);

        QMetaObject::connectSlotsByName(N_chat);
    } // setupUi

    void retranslateUi(QWidget *N_chat)
    {
        N_chat->setWindowTitle(QApplication::translate("N_chat", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class N_chat: public Ui_N_chat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_N_CHAT_H
