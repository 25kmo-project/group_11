#include "cardwithdrawwindow.h"
#include "ui_cardwithdrawwindow.h"

CardWithdrawWindow::CardWithdrawWindow(Account *newAccount, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CardWithdrawWindow)
    , account(newAccount)
{
    ui->setupUi(this);
}

CardWithdrawWindow::~CardWithdrawWindow()
{
    delete ui;
}
