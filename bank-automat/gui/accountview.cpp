#include "accountview.h"
#include "ui_accountview.h"
#include "carddepositwindow.h"
#include "cardwithdrawwindow.h"
#include "transactionview.h"

AccountView::AccountView(QString newAccountId, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AccountView)
    , account(new Account(newAccountId))
{
    ui->setupUi(this);

    //connect(ui->btnTestButton, &QPushButton::clicked, this, &AccountView::btnTestButtonSlot);
    connect(ui->btnDeposit, &QPushButton::clicked, this, &AccountView::btnDepositButtonSlot);
    connect(ui->btnWithdraw, &QPushButton::clicked, this, &AccountView::btnWithdrawButtonSlot);
    connect(ui->btnShowTransactions, &QPushButton::clicked, this, &AccountView::btnShowTransactionsSlot);
    connect(ui->btnLogout, &QPushButton::clicked, this, &AccountView::btnLogoutSlot);
    connect(account, &Account::accountDataReady, this, &AccountView::initializeViewSlot);

    AccountView::updateBalanceLabel();

    connect(account, &Account::balanceChanged, this, &AccountView::updateBalanceLabel);
}

AccountView::~AccountView()
{
    // Emit a signal so that MainWindow can clean up after this is destroyed
    emit userLogoutSignal();
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

void AccountView::initializeViewSlot()
{
    ui->labelOwnerId->setText(QString::number(account->getIdOwner()));
    customer = new Customer(account->getIdOwner(), this);
    connect(customer, &Customer::customerDataReady, this, &AccountView::updateCustomerLabel);
}

void AccountView::updateCustomerLabel()
{
    QString fullName = customer->getFname() + " " + customer->getLname();
    ui->labelOwnerFullName->setText(fullName);
}

void AccountView::btnDepositButtonSlot()
{
    //on deposit clicked, deposit window opens
    CardDepositWindow *objCardDeposit = new CardDepositWindow(account, this);
    ui->stackedWidget->addWidget(objCardDeposit);
    ui->stackedWidget->setCurrentWidget(objCardDeposit);
    connect(objCardDeposit, &CardDepositWindow::closeViewSignal, this, &AccountView::closeViewSlot);

    //connect signal and balance update function

    // Connect signal for return message to user
    connect(objCardDeposit, &CardDepositWindow::infoMessage, this, &AccountView::showInfoLabelSlot);
    //after successfull deposit:
    //objCardDeposit closes
    //Message for user
}

void AccountView::btnShowTransactionsSlot()
{
    TransactionView *objTransactionView = new TransactionView(account, this);
    ui->stackedWidget->addWidget(objTransactionView);
    ui->stackedWidget->setCurrentWidget(objTransactionView);
    connect(objTransactionView, &TransactionView::closeViewSignal, this, &AccountView::closeViewSlot);
}

void AccountView::btnWithdrawButtonSlot()
{
    CardWithdrawWindow *objCardWithdraw = new CardWithdrawWindow(account, this);
    ui->stackedWidget->addWidget(objCardWithdraw);
    ui->stackedWidget->setCurrentWidget(objCardWithdraw);
    // Signal used when withdraw is canceled/successful and view needs to be closed
    connect(objCardWithdraw, &CardWithdrawWindow::closeViewSignal, this, &AccountView::closeViewSlot);

    // Connect signal for return message to user
    connect(objCardWithdraw, &CardWithdrawWindow::infoMessage, this, &AccountView::showInfoLabelSlot);
}

void AccountView::btnLogoutSlot()
{
    this->deleteLater();
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

void AccountView::closeViewSlot() {
    // Remove previous view from the stacked widget and change back to the AccountView page
    QWidget *previousView = ui->stackedWidget->currentWidget();
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->removeWidget(previousView);
}

void AccountView::getCustomerDataSlot()
{

}
