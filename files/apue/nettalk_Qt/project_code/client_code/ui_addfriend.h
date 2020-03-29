/********************************************************************************
** Form generated from reading UI file 'addfriend.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDFRIEND_H
#define UI_ADDFRIEND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddFriend
{
public:

    void setupUi(QWidget *AddFriend)
    {
        if (AddFriend->objectName().isEmpty())
            AddFriend->setObjectName(QStringLiteral("AddFriend"));
        AddFriend->resize(400, 300);

        retranslateUi(AddFriend);

        QMetaObject::connectSlotsByName(AddFriend);
    } // setupUi

    void retranslateUi(QWidget *AddFriend)
    {
        AddFriend->setWindowTitle(QApplication::translate("AddFriend", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AddFriend: public Ui_AddFriend {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDFRIEND_H
