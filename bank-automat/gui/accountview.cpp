#include "accountview.h"
#include "ui_accountview.h"
#include "carddepositwindow.h"
#include "cardwithdrawwindow.h"

AccountView::AccountView(Account *newAccount, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AccountView)
    , account(newAccount)
{
    ui->setupUi(this);
    connect(ui->btnTestButton, &QPushButton::clicked, this, &AccountView::btnTestButtonSlot);
    connect(ui->btnDeposit, &QPushButton::clicked, this, &AccountView::btnDepositButtonSlot);
    connect(ui->btnWithdraw, &QPushButton::clicked, this, &AccountView::btnWithdrawButtonSlot);
    ui->labelInfo->setText("Tervetuloa!");
    AccountView::updateBalanceLabel(account->getBalance());
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
    connect(objCardDeposit, &CardDepositWindow::balanceChanged, this, &AccountView::updateBalanceLabel);
    objCardDeposit->show();
    //after successfull deposit:
    //objCardDeposit closes
    //Message for user
    ui->labelInfo->setText("Talletus onnistui!");
}

void AccountView::btnWithdrawButtonSlot()
{
    CardWithdrawWindow *objCardWithdraw = new CardWithdrawWindow(account, this);
    objCardWithdraw->show();
}

void AccountView::updateBalanceLabel(qint64 newBalance)
{

    ui->labelBalance->setText(
        QString::number(newBalance / 100.0, 'f', 2)
    );
}
