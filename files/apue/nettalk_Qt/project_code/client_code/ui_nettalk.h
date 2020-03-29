/********************************************************************************
** Form generated from reading UI file 'nettalk.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETTALK_H
#define UI_NETTALK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_Nettalk
{
public:

    void setupUi(QDialog *Nettalk)
    {
        if (Nettalk->objectName().isEmpty())
            Nettalk->setObjectName(QStringLiteral("Nettalk"));
        Nettalk->resize(400, 300);

        retranslateUi(Nettalk);

        QMetaObject::connectSlotsByName(Nettalk);
    } // setupUi

    void retranslateUi(QDialog *Nettalk)
    {
        Nettalk->setWindowTitle(QApplication::translate("Nettalk", "Nettalk", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Nettalk: public Ui_Nettalk {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETTALK_H
