/********************************************************************************
** Form generated from reading UI file 'addaccountmenu.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDACCOUNTMENU_H
#define UI_ADDACCOUNTMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_addaccountmenu
{
public:
    QLineEdit *textAddAccountId;
    QLabel *label;
    QLineEdit *textBalance;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *textCreditLimit;
    QLabel *label_4;
    QLineEdit *textOwnerId;
    QLabel *label_5;
    QLabel *label_7;
    QPushButton *btnAddAccount;
    QLabel *hint;
    QLabel *hint2;
    QLineEdit *textDeleteAccountId;
    QPushButton *btnDeleteAccount;
    QLabel *labelInfo;
    QComboBox *comboAccountType;

    void setupUi(QDialog *addaccountmenu)
    {
        if (addaccountmenu->objectName().isEmpty())
            addaccountmenu->setObjectName("addaccountmenu");
        addaccountmenu->resize(504, 341);
        textAddAccountId = new QLineEdit(addaccountmenu);
        textAddAccountId->setObjectName("textAddAccountId");
        textAddAccountId->setGeometry(QRect(120, 40, 141, 31));
        label = new QLabel(addaccountmenu);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 40, 121, 31));
        textBalance = new QLineEdit(addaccountmenu);
        textBalance->setObjectName("textBalance");
        textBalance->setGeometry(QRect(120, 80, 141, 31));
        label_2 = new QLabel(addaccountmenu);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(18, 79, 121, 31));
        label_3 = new QLabel(addaccountmenu);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(18, 119, 121, 31));
        textCreditLimit = new QLineEdit(addaccountmenu);
        textCreditLimit->setObjectName("textCreditLimit");
        textCreditLimit->setGeometry(QRect(120, 160, 141, 31));
        label_4 = new QLabel(addaccountmenu);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(18, 159, 121, 31));
        textOwnerId = new QLineEdit(addaccountmenu);
        textOwnerId->setObjectName("textOwnerId");
        textOwnerId->setGeometry(QRect(120, 200, 141, 31));
        label_5 = new QLabel(addaccountmenu);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(18, 199, 121, 31));
        label_7 = new QLabel(addaccountmenu);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(270, 160, 211, 31));
        btnAddAccount = new QPushButton(addaccountmenu);
        btnAddAccount->setObjectName("btnAddAccount");
        btnAddAccount->setGeometry(QRect(270, 200, 141, 31));
        hint = new QLabel(addaccountmenu);
        hint->setObjectName("hint");
        hint->setGeometry(QRect(130, 0, 111, 41));
        QFont font;
        font.setPointSize(11);
        hint->setFont(font);
        hint2 = new QLabel(addaccountmenu);
        hint2->setObjectName("hint2");
        hint2->setGeometry(QRect(130, 250, 151, 41));
        hint2->setFont(font);
        textDeleteAccountId = new QLineEdit(addaccountmenu);
        textDeleteAccountId->setObjectName("textDeleteAccountId");
        textDeleteAccountId->setGeometry(QRect(120, 290, 141, 31));
        btnDeleteAccount = new QPushButton(addaccountmenu);
        btnDeleteAccount->setObjectName("btnDeleteAccount");
        btnDeleteAccount->setGeometry(QRect(270, 290, 141, 31));
        labelInfo = new QLabel(addaccountmenu);
        labelInfo->setObjectName("labelInfo");
        labelInfo->setGeometry(QRect(270, 240, 191, 41));
        labelInfo->setFont(font);
        comboAccountType = new QComboBox(addaccountmenu);
        comboAccountType->setObjectName("comboAccountType");
        comboAccountType->setGeometry(QRect(120, 120, 141, 31));

        retranslateUi(addaccountmenu);

        QMetaObject::connectSlotsByName(addaccountmenu);
    } // setupUi

    void retranslateUi(QDialog *addaccountmenu)
    {
        addaccountmenu->setWindowTitle(QCoreApplication::translate("addaccountmenu", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("addaccountmenu", "Account ID", nullptr));
        label_2->setText(QCoreApplication::translate("addaccountmenu", "Balance", nullptr));
        label_3->setText(QCoreApplication::translate("addaccountmenu", "Type", nullptr));
        label_4->setText(QCoreApplication::translate("addaccountmenu", "Credit limit", nullptr));
        label_5->setText(QCoreApplication::translate("addaccountmenu", "Owner ID", nullptr));
        label_7->setText(QCoreApplication::translate("addaccountmenu", "(Will be 0, if type = DEBIT)", nullptr));
        btnAddAccount->setText(QCoreApplication::translate("addaccountmenu", "Add account", nullptr));
        hint->setText(QCoreApplication::translate("addaccountmenu", "Add Account", nullptr));
        hint2->setText(QCoreApplication::translate("addaccountmenu", "Delete by ID", nullptr));
        btnDeleteAccount->setText(QCoreApplication::translate("addaccountmenu", "Delete acount", nullptr));
        labelInfo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class addaccountmenu: public Ui_addaccountmenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDACCOUNTMENU_H
