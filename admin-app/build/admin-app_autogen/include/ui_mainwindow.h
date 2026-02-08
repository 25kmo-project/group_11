/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *btnLogin;
    QLabel *title;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *textCardId;
    QLineEdit *textPin;
    QLabel *labelInfo;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(372, 366);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        btnLogin = new QPushButton(centralwidget);
        btnLogin->setObjectName("btnLogin");
        btnLogin->setGeometry(QRect(130, 200, 141, 41));
        title = new QLabel(centralwidget);
        title->setObjectName("title");
        title->setGeometry(QRect(90, 20, 201, 51));
        QFont font;
        font.setPointSize(24);
        font.setBold(true);
        title->setFont(font);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 110, 91, 21));
        QFont font1;
        font1.setPointSize(12);
        label_2->setFont(font1);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(40, 150, 81, 31));
        label_3->setFont(font1);
        textCardId = new QLineEdit(centralwidget);
        textCardId->setObjectName("textCardId");
        textCardId->setGeometry(QRect(130, 101, 141, 31));
        textPin = new QLineEdit(centralwidget);
        textPin->setObjectName("textPin");
        textPin->setGeometry(QRect(130, 150, 141, 31));
        textPin->setEchoMode(QLineEdit::EchoMode::Password);
        labelInfo = new QLabel(centralwidget);
        labelInfo->setObjectName("labelInfo");
        labelInfo->setGeometry(QRect(70, 270, 261, 41));
        labelInfo->setFont(font1);
        labelInfo->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 372, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnLogin->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        title->setText(QCoreApplication::translate("MainWindow", "ATM Login", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Card ID", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "PIN", nullptr));
        labelInfo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
