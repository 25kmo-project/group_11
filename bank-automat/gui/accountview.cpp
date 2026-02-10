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

    // Connect signal for return message to user
    connect(objCardDeposit, &CardDepositWindow::infoMessage, this, &AccountView::showInfoLabelSlot);
    objCardDeposit->show();
    //after successfull deposit:
    //objCardDeposit closes
    //Message for user
}

void AccountView::btnShowTransactionsSlot()
{
    TransactionView *objTransactionView = new TransactionView(account, this);
    objTransactionView->show();
}

void AccountView::btnWithdrawButtonSlot()
{
    CardWithdrawWindow *objCardWithdraw = new CardWithdrawWindow(account, this);
    // Connect signal for return message to user
    connect(objCardWithdraw, &CardWithdrawWindow::infoMessage, this, &AccountView::showInfoLabelSlot);
    objCardWithdraw->show();
}

void AccountView::showInfoLabelSlot(const QString &text)
{
    ui->labelInfo->setText(text);
    QTimer::singleShot(4000,this,[this]() {
        ui->labelInfo->clear();
    });
}

void AccountView::updateBalanceLabel()
{
    qint64 balance = this->account->getBalance();
    ui->labelBalance->setText(
        QString::number(balance / 100.0, 'f', 2)
    );
}


