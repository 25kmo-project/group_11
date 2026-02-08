/********************************************************************************
** Form generated from reading UI file 'customersmenu.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMERSMENU_H
#define UI_CUSTOMERSMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_customersmenu
{
public:
    QPushButton *btnGetCustomers;
    QTableView *tableCustomers;
    QPushButton *btnAddNewCustomer;
    QPushButton *btnGetCustomerById;
    QLabel *label;
    QLineEdit *textCustomerId;
    QLabel *labelInfo;

    void setupUi(QDialog *customersmenu)
    {
        if (customersmenu->objectName().isEmpty())
            customersmenu->setObjectName("customersmenu");
        customersmenu->resize(633, 364);
        btnGetCustomers = new QPushButton(customersmenu);
        btnGetCustomers->setObjectName("btnGetCustomers");
        btnGetCustomers->setGeometry(QRect(20, 20, 181, 31));
        tableCustomers = new QTableView(customersmenu);
        tableCustomers->setObjectName("tableCustomers");
        tableCustomers->setGeometry(QRect(20, 100, 591, 231));
        btnAddNewCustomer = new QPushButton(customersmenu);
        btnAddNewCustomer->setObjectName("btnAddNewCustomer");
        btnAddNewCustomer->setGeometry(QRect(210, 20, 191, 31));
        btnGetCustomerById = new QPushButton(customersmenu);
        btnGetCustomerById->setObjectName("btnGetCustomerById");
        btnGetCustomerById->setGeometry(QRect(20, 60, 181, 31));
        label = new QLabel(customersmenu);
        label->setObjectName("label");
        label->setGeometry(QRect(370, 60, 51, 31));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        textCustomerId = new QLineEdit(customersmenu);
        textCustomerId->setObjectName("textCustomerId");
        textCustomerId->setGeometry(QRect(210, 60, 141, 31));
        labelInfo = new QLabel(customersmenu);
        labelInfo->setObjectName("labelInfo");
        labelInfo->setGeometry(QRect(400, 60, 211, 31));
        labelInfo->setFont(font);

        retranslateUi(customersmenu);

        QMetaObject::connectSlotsByName(customersmenu);
    } // setupUi

    void retranslateUi(QDialog *customersmenu)
    {
        customersmenu->setWindowTitle(QCoreApplication::translate("customersmenu", "Dialog", nullptr));
        btnGetCustomers->setText(QCoreApplication::translate("customersmenu", "Get all customers", nullptr));
        btnAddNewCustomer->setText(QCoreApplication::translate("customersmenu", "Add/delete customer", nullptr));
        btnGetCustomerById->setText(QCoreApplication::translate("customersmenu", "Get customer by id", nullptr));
        label->setText(QCoreApplication::translate("customersmenu", "ID", nullptr));
        labelInfo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class customersmenu: public Ui_customersmenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMERSMENU_H
