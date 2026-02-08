/********************************************************************************
** Form generated from reading UI file 'accountsmenu.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACCOUNTSMENU_H
#define UI_ACCOUNTSMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_accountsmenu
{
public:
    QPushButton *btnGetAccounts;
    QPushButton *btnCreateDeleteAccount;
    QTableView *tableAccounts;
    QPushButton *btnGetAccountById;
    QLineEdit *textAccountId;
    QLabel *label;
    QLabel *labelInfo;
    QLabel *title;

    void setupUi(QDialog *accountsmenu)
    {
        if (accountsmenu->objectName().isEmpty())
            accountsmenu->setObjectName("accountsmenu");
        accountsmenu->resize(614, 378);
        btnGetAccounts = new QPushButton(accountsmenu);
        btnGetAccounts->setObjectName("btnGetAccounts");
        btnGetAccounts->setGeometry(QRect(30, 60, 151, 31));
        btnCreateDeleteAccount = new QPushButton(accountsmenu);
        btnCreateDeleteAccount->setObjectName("btnCreateDeleteAccount");
        btnCreateDeleteAccount->setGeometry(QRect(200, 60, 181, 31));
        tableAccounts = new QTableView(accountsmenu);
        tableAccounts->setObjectName("tableAccounts");
        tableAccounts->setGeometry(QRect(30, 140, 551, 201));
        btnGetAccountById = new QPushButton(accountsmenu);
        btnGetAccountById->setObjectName("btnGetAccountById");
        btnGetAccountById->setGeometry(QRect(30, 100, 151, 31));
        textAccountId = new QLineEdit(accountsmenu);
        textAccountId->setObjectName("textAccountId");
        textAccountId->setGeometry(QRect(200, 100, 151, 31));
        label = new QLabel(accountsmenu);
        label->setObjectName("label");
        label->setGeometry(QRect(360, 100, 41, 31));
        QFont font;
        font.setPointSize(12);
        font.setBold(false);
        label->setFont(font);
        labelInfo = new QLabel(accountsmenu);
        labelInfo->setObjectName("labelInfo");
        labelInfo->setGeometry(QRect(390, 110, 211, 31));
        labelInfo->setFont(font);
        title = new QLabel(accountsmenu);
        title->setObjectName("title");
        title->setGeometry(QRect(110, 10, 511, 41));
        QFont font1;
        font1.setPointSize(20);
        font1.setBold(true);
        title->setFont(font1);

        retranslateUi(accountsmenu);

        QMetaObject::connectSlotsByName(accountsmenu);
    } // setupUi

    void retranslateUi(QDialog *accountsmenu)
    {
        accountsmenu->setWindowTitle(QCoreApplication::translate("accountsmenu", "Dialog", nullptr));
        btnGetAccounts->setText(QCoreApplication::translate("accountsmenu", "Get all accounts", nullptr));
        btnCreateDeleteAccount->setText(QCoreApplication::translate("accountsmenu", "Create/Delete account", nullptr));
        btnGetAccountById->setText(QCoreApplication::translate("accountsmenu", "Get by id", nullptr));
        label->setText(QCoreApplication::translate("accountsmenu", "ID", nullptr));
        labelInfo->setText(QString());
        title->setText(QCoreApplication::translate("accountsmenu", "ACCOUNT MANAGEMENT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class accountsmenu: public Ui_accountsmenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCOUNTSMENU_H
