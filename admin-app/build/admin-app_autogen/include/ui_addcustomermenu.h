/********************************************************************************
** Form generated from reading UI file 'addcustomermenu.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCUSTOMERMENU_H
#define UI_ADDCUSTOMERMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_addcustomermenu
{
public:
    QLabel *label;
    QLineEdit *textFirstName;
    QLineEdit *textLastName;
    QLabel *label_2;
    QLineEdit *textStreetAddress;
    QLabel *label_3;
    QLineEdit *textCity;
    QLabel *label_4;
    QPushButton *btnSendCustomerData;
    QLabel *labelInfo;
    QLabel *hint1;
    QLabel *hint2;
    QLabel *label_7;
    QLineEdit *textCustomerId;
    QPushButton *btnSendDeleteCustomer;

    void setupUi(QDialog *addcustomermenu)
    {
        if (addcustomermenu->objectName().isEmpty())
            addcustomermenu->setObjectName("addcustomermenu");
        addcustomermenu->resize(457, 331);
        label = new QLabel(addcustomermenu);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 40, 111, 31));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);
        textFirstName = new QLineEdit(addcustomermenu);
        textFirstName->setObjectName("textFirstName");
        textFirstName->setGeometry(QRect(110, 40, 121, 31));
        textLastName = new QLineEdit(addcustomermenu);
        textLastName->setObjectName("textLastName");
        textLastName->setGeometry(QRect(110, 90, 121, 31));
        label_2 = new QLabel(addcustomermenu);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 90, 111, 31));
        label_2->setFont(font);
        textStreetAddress = new QLineEdit(addcustomermenu);
        textStreetAddress->setObjectName("textStreetAddress");
        textStreetAddress->setGeometry(QRect(110, 140, 121, 31));
        label_3 = new QLabel(addcustomermenu);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 140, 111, 31));
        label_3->setFont(font);
        textCity = new QLineEdit(addcustomermenu);
        textCity->setObjectName("textCity");
        textCity->setGeometry(QRect(110, 190, 121, 31));
        label_4 = new QLabel(addcustomermenu);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 190, 111, 31));
        label_4->setFont(font);
        btnSendCustomerData = new QPushButton(addcustomermenu);
        btnSendCustomerData->setObjectName("btnSendCustomerData");
        btnSendCustomerData->setGeometry(QRect(250, 190, 161, 31));
        labelInfo = new QLabel(addcustomermenu);
        labelInfo->setObjectName("labelInfo");
        labelInfo->setGeometry(QRect(250, 230, 191, 31));
        QFont font1;
        font1.setPointSize(12);
        labelInfo->setFont(font1);
        hint1 = new QLabel(addcustomermenu);
        hint1->setObjectName("hint1");
        hint1->setGeometry(QRect(120, 0, 171, 41));
        hint1->setFont(font1);
        hint2 = new QLabel(addcustomermenu);
        hint2->setObjectName("hint2");
        hint2->setGeometry(QRect(120, 230, 141, 41));
        hint2->setFont(font1);
        label_7 = new QLabel(addcustomermenu);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 270, 131, 31));
        label_7->setFont(font);
        textCustomerId = new QLineEdit(addcustomermenu);
        textCustomerId->setObjectName("textCustomerId");
        textCustomerId->setGeometry(QRect(110, 270, 121, 31));
        btnSendDeleteCustomer = new QPushButton(addcustomermenu);
        btnSendDeleteCustomer->setObjectName("btnSendDeleteCustomer");
        btnSendDeleteCustomer->setGeometry(QRect(250, 270, 161, 31));

        retranslateUi(addcustomermenu);

        QMetaObject::connectSlotsByName(addcustomermenu);
    } // setupUi

    void retranslateUi(QDialog *addcustomermenu)
    {
        addcustomermenu->setWindowTitle(QCoreApplication::translate("addcustomermenu", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("addcustomermenu", "First name", nullptr));
        label_2->setText(QCoreApplication::translate("addcustomermenu", "Last name", nullptr));
        label_3->setText(QCoreApplication::translate("addcustomermenu", "Street", nullptr));
        label_4->setText(QCoreApplication::translate("addcustomermenu", "City", nullptr));
        btnSendCustomerData->setText(QCoreApplication::translate("addcustomermenu", "Add customer", nullptr));
        labelInfo->setText(QString());
        hint1->setText(QCoreApplication::translate("addcustomermenu", "Add customer", nullptr));
        hint2->setText(QCoreApplication::translate("addcustomermenu", "Delete", nullptr));
        label_7->setText(QCoreApplication::translate("addcustomermenu", "Customer ID", nullptr));
        btnSendDeleteCustomer->setText(QCoreApplication::translate("addcustomermenu", "Delete customer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class addcustomermenu: public Ui_addcustomermenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCUSTOMERMENU_H
