/********************************************************************************
** Form generated from reading UI file 'adminmenu.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINMENU_H
#define UI_ADMINMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_adminmenu
{
public:
    QPushButton *btnCustomers;
    QPushButton *btnAccounts;
    QPushButton *btnCards;
    QLabel *title;

    void setupUi(QDialog *adminmenu)
    {
        if (adminmenu->objectName().isEmpty())
            adminmenu->setObjectName("adminmenu");
        adminmenu->resize(559, 402);
        btnCustomers = new QPushButton(adminmenu);
        btnCustomers->setObjectName("btnCustomers");
        btnCustomers->setGeometry(QRect(70, 90, 171, 51));
        btnAccounts = new QPushButton(adminmenu);
        btnAccounts->setObjectName("btnAccounts");
        btnAccounts->setGeometry(QRect(70, 150, 171, 51));
        btnCards = new QPushButton(adminmenu);
        btnCards->setObjectName("btnCards");
        btnCards->setGeometry(QRect(260, 90, 171, 51));
        title = new QLabel(adminmenu);
        title->setObjectName("title");
        title->setGeometry(QRect(140, 20, 311, 51));
        QFont font;
        font.setPointSize(20);
        title->setFont(font);

        retranslateUi(adminmenu);

        QMetaObject::connectSlotsByName(adminmenu);
    } // setupUi

    void retranslateUi(QDialog *adminmenu)
    {
        adminmenu->setWindowTitle(QCoreApplication::translate("adminmenu", "Dialog", nullptr));
        btnCustomers->setText(QCoreApplication::translate("adminmenu", "Customers management", nullptr));
        btnAccounts->setText(QCoreApplication::translate("adminmenu", "Account management", nullptr));
        btnCards->setText(QCoreApplication::translate("adminmenu", "Cards management", nullptr));
        title->setText(QCoreApplication::translate("adminmenu", "ADMIN PANEL", nullptr));
    } // retranslateUi

};

namespace Ui {
    class adminmenu: public Ui_adminmenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINMENU_H
