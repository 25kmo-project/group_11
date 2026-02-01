#include "accountview.h"
#include "ui_accountview.h"
#include "carddepositwindow.h"

accountview::accountview(Account &newAccount, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::accountview)
    , account(newAccount)
{
    ui->setupUi(this);
    connect(ui->btnTestButton, &QPushButton::clicked, this, &accountview::btnTestButtonSlot);
    connect(ui->btnDeposit, &QPushButton::clicked, this, &accountview::btnDepositButtonSlot);
}

accountview::~accountview()
{
    delete ui;
}

void accountview::btnTestButtonSlot()
{
    qDebug() << "Account ID:" << account.getIdAccount();
    qDebug() << "Owner ID:" << account.getIdOwner();
    qDebug() << "Balance:" << account.getBalance();
    qDebug() << "Credit limit:" << account.getCreditLimit();
    qDebug() << "Type:" << account.getAccountType();
}

void accountview::btnDepositButtonSlot()
{
    //on deposit clicked, deposit window opens
    CardDepositWindow *objCardDeposit = new CardDepositWindow(account, this);
    objCardDeposit->show();
    //after successfull deposit:
    //objCardDeposit closes
    //Message for user
    ui->labelInfo->setText("Talletus onnistui!");
}
