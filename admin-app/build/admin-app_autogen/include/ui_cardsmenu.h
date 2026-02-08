/********************************************************************************
** Form generated from reading UI file 'cardsmenu.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CARDSMENU_H
#define UI_CARDSMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_cardsmenu
{
public:
    QPushButton *btnGetAllCards;
    QPushButton *btnGetCardById;
    QPushButton *btnAddDeleteCards;
    QLineEdit *textCardId;
    QLabel *label;
    QTableView *tableCards;
    QPushButton *btnGetLockedCards;
    QPushButton *btnResetLockedCardById;
    QLabel *labelInfo;
    QLabel *title;
    QPushButton *btnAddDeleteCards_2;

    void setupUi(QDialog *cardsmenu)
    {
        if (cardsmenu->objectName().isEmpty())
            cardsmenu->setObjectName("cardsmenu");
        cardsmenu->resize(499, 467);
        btnGetAllCards = new QPushButton(cardsmenu);
        btnGetAllCards->setObjectName("btnGetAllCards");
        btnGetAllCards->setGeometry(QRect(20, 70, 211, 31));
        btnGetCardById = new QPushButton(cardsmenu);
        btnGetCardById->setObjectName("btnGetCardById");
        btnGetCardById->setGeometry(QRect(130, 110, 101, 31));
        btnAddDeleteCards = new QPushButton(cardsmenu);
        btnAddDeleteCards->setObjectName("btnAddDeleteCards");
        btnAddDeleteCards->setGeometry(QRect(20, 210, 201, 31));
        textCardId = new QLineEdit(cardsmenu);
        textCardId->setObjectName("textCardId");
        textCardId->setGeometry(QRect(60, 110, 61, 31));
        label = new QLabel(cardsmenu);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 110, 51, 31));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);
        tableCards = new QTableView(cardsmenu);
        tableCards->setObjectName("tableCards");
        tableCards->setGeometry(QRect(240, 70, 221, 341));
        btnGetLockedCards = new QPushButton(cardsmenu);
        btnGetLockedCards->setObjectName("btnGetLockedCards");
        btnGetLockedCards->setGeometry(QRect(20, 150, 211, 31));
        btnResetLockedCardById = new QPushButton(cardsmenu);
        btnResetLockedCardById->setObjectName("btnResetLockedCardById");
        btnResetLockedCardById->setGeometry(QRect(20, 290, 201, 31));
        labelInfo = new QLabel(cardsmenu);
        labelInfo->setObjectName("labelInfo");
        labelInfo->setGeometry(QRect(20, 370, 191, 41));
        QFont font1;
        font1.setPointSize(12);
        labelInfo->setFont(font1);
        title = new QLabel(cardsmenu);
        title->setObjectName("title");
        title->setGeometry(QRect(90, 10, 471, 41));
        QFont font2;
        font2.setPointSize(20);
        title->setFont(font2);
        btnAddDeleteCards_2 = new QPushButton(cardsmenu);
        btnAddDeleteCards_2->setObjectName("btnAddDeleteCards_2");
        btnAddDeleteCards_2->setGeometry(QRect(20, 250, 201, 31));

        retranslateUi(cardsmenu);

        QMetaObject::connectSlotsByName(cardsmenu);
    } // setupUi

    void retranslateUi(QDialog *cardsmenu)
    {
        cardsmenu->setWindowTitle(QCoreApplication::translate("cardsmenu", "Dialog", nullptr));
        btnGetAllCards->setText(QCoreApplication::translate("cardsmenu", "Get all cards", nullptr));
        btnGetCardById->setText(QCoreApplication::translate("cardsmenu", "Get By ID", nullptr));
        btnAddDeleteCards->setText(QCoreApplication::translate("cardsmenu", "Add card", nullptr));
        label->setText(QCoreApplication::translate("cardsmenu", "ID", nullptr));
        btnGetLockedCards->setText(QCoreApplication::translate("cardsmenu", "Get locked cards", nullptr));
        btnResetLockedCardById->setText(QCoreApplication::translate("cardsmenu", "Reset lock in selected", nullptr));
        labelInfo->setText(QString());
        title->setText(QCoreApplication::translate("cardsmenu", "CARD MANAGEMENT", nullptr));
        btnAddDeleteCards_2->setText(QCoreApplication::translate("cardsmenu", "Delete selected", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cardsmenu: public Ui_cardsmenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARDSMENU_H
