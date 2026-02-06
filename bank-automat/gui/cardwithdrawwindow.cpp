#include "cardwithdrawwindow.h"
#include "ui_cardwithdrawwindow.h"

CardWithdrawWindow::CardWithdrawWindow(Account *newAccount, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CardWithdrawWindow)
    , account(newAccount)
{
    ui->setupUi(this);

    connect(ui->button20, &QPushButton::clicked, this, &CardWithdrawWindow::clickedAmountSlot);
    connect(ui->button40, &QPushButton::clicked, this, &CardWithdrawWindow::clickedAmountSlot);
    connect(ui->button50, &QPushButton::clicked, this, &CardWithdrawWindow::clickedAmountSlot);
    connect(ui->button100, &QPushButton::clicked, this, &CardWithdrawWindow::clickedAmountSlot);
    connect(ui->buttonOther, &QPushButton::clicked, this, &CardWithdrawWindow::clickedOtherAmountSlot);

    connect(ui->buttonConfirm, &QPushButton::clicked, this, &CardWithdrawWindow::confirmOtherWithdrawSlot);

    connect(ui->buttonCancel, &QPushButton::clicked, this, &CardWithdrawWindow::cancelWithdrawSlot);
    connect(ui->buttonCancel_2, &QPushButton::clicked, this, &CardWithdrawWindow::cancelWithdrawSlot);
}

CardWithdrawWindow::~CardWithdrawWindow()
{
    delete ui;
}

void CardWithdrawWindow::clickedAmountSlot() {
    double amount = sender()->property("value").toDouble();
    qDebug() << amount;
    this->close();
}

void CardWithdrawWindow::clickedOtherAmountSlot() {
    ui->stackedWidget->setCurrentIndex(1);
}

void CardWithdrawWindow::confirmOtherWithdrawSlot() {
    double amount =  ui->amountLineEdit->text().toDouble();
    qDebug() << amount;
    this->close();
}

void CardWithdrawWindow::cancelWithdrawSlot() {
    this->close();
}
