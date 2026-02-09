#include "accountview.h"
#include "ui_accountview.h"
#include "carddepositwindow.h"
#include "cardwithdrawwindow.h"
#include "transactionview.h"

AccountView::AccountView(QString newAccountId, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AccountView)
    , account(new Account(newAccountId))
{
    ui->setupUi(this);

    connect(ui->btnTestButton, &QPushButton::clicked, this, &AccountView::btnTestButtonSlot);
    connect(ui->btnDeposit, &QPushButton::clicked, this, &AccountView::btnDepositButtonSlot);
    connect(ui->btnWithdraw, &QPushButton::clicked, this, &AccountView::btnWithdrawButtonSlot);
    connect(ui->btnShowTransactions, &QPushButton::clicked, this, &AccountView::btnShowTransactionsSlot);

    ui->labelInfo->setText("Tervetuloa!");
    AccountView::updateBalanceLabel();

    connect(account, &Account::balanceChanged, this, &AccountView::updateBalanceLabel);
}

AccountView::~AccountView()
{
    delete ui;
}

void AccountView::btnTestButtonSlot()
{
    qDebug() << "Account ID:" << account->getIdAccount();
    qDebug() << "Owner ID:" << account->getIdOwner();
    qDebug() << "Balance:" << account->getBalance();
    qDebug() << "Credit limit:" << account->getCreditLimit();
    qDebug() << "Type:" << account->getAccountType();
}

void AccountView::btnDepositButtonSlot()
{
    //on deposit clicked, deposit window opens
    CardDepositWindow *objCardDeposit = new CardDepositWindow(account, this);
    //connect signal and balance update function
    objCardDeposit->show();
    //after successfull deposit:
    //objCardDeposit closes
    //Message for user
    ui->labelInfo->setText("Talletus onnistui!");
}

void AccountView::btnShowTransactionsSlot()
{
    TransactionView *objTransactionView = new TransactionView(account, this);
    objTransactionView->show();
}

void AccountView::btnWithdrawButtonSlot()
{
    CardWithdrawWindow *objCardWithdraw = new CardWithdrawWindow(account, this);
    objCardWithdraw->show();
}

void AccountView::updateBalanceLabel()
{
    qint64 balance = this->account->getBalance();
    ui->labelBalance->setText(
        QString::number(balance / 100.0, 'f', 2)
    );
}
