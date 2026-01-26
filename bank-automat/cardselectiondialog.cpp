#include "cardselectiondialog.h"
#include "ui_cardselectiondialog.h"


cardselectiondialog::cardselectiondialog(QJsonArray accounts, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cardselectiondialog)
{
    ui->setupUi(this);
    qDebug().noquote() << accounts;
    this->accounts = accounts;
    connect(ui->btnChooseCredit, &QPushButton::clicked, this, &cardselectiondialog::btnCreditAccount);
    connect(ui->btnChooseDebit, &QPushButton::clicked, this, &cardselectiondialog::btnDebitAccount);
}

cardselectiondialog::~cardselectiondialog()
{
    delete ui;
}

void cardselectiondialog::btnCreditAccount()
{
    QJsonObject objCard1 = accounts.at(0).toObject();
    QJsonObject objCard2 = accounts.at(1).toObject();

    if (objCard1["account_type"].toString() == "CREDIT") {
        // Data handling to construct creditaccountwindow
        QString idAccount = objCard1["idaccount"].toString();

        QString cardBalanceString = objCard1["balance"].toString();
        cardBalanceString.remove('.');
        qint64 cardBalanceCents = cardBalanceString.toLongLong();

        QString cardCreditLimitCentsString = objCard1["credit_limit"].toString();
        cardCreditLimitCentsString.remove('.');
        qint64 cardCreditLimitCents = cardCreditLimitCentsString.toLongLong();

        // Construct window with required parameters
        creditaccountwindow *objCreditAccountWindow = new creditaccountwindow(idAccount, cardBalanceCents, cardCreditLimitCents);
        objCreditAccountWindow->show();
    } else {
        // Data handling to construct creditaccountwindow
        QString idAccount = objCard2["idaccount"].toString();

        QString cardBalanceString = objCard2["balance"].toString();
        cardBalanceString.remove('.');
        qint64 cardBalanceCents = cardBalanceString.toLongLong();

        QString cardCreditLimitCentsString = objCard2["credit_limit"].toString();
        cardCreditLimitCentsString.remove('.');
        qint64 cardCreditLimitCents = cardCreditLimitCentsString.toLongLong();

        // Construct window with required parameters
        creditaccountwindow *objCreditAccountWindow = new creditaccountwindow(idAccount, cardBalanceCents, cardCreditLimitCents);
        objCreditAccountWindow->show();
    }
}

void cardselectiondialog::btnDebitAccount()
{
    QJsonObject objCard1 = accounts.at(0).toObject();
    QJsonObject objCard2 = accounts.at(1).toObject();

    if (objCard1["account_type"].toString() == "DEBIT") {
        // Data handling to construct debitaccountwindow
        QString idAccount = objCard1["idaccount"].toString();

        QString cardBalanceString = objCard1["balance"].toString();
        cardBalanceString.remove('.');
        qint64 cardBalanceCents = cardBalanceString.toLongLong();

        // Construct window with required parameters
        debitaccountwindow *objDebitAccountWindow = new debitaccountwindow(idAccount, cardBalanceCents);
        objDebitAccountWindow->show();
    } else {
        // Data handling to construct debitaccountwindow
        QString idAccount = objCard2["idaccount"].toString();

        QString cardBalanceString = objCard2["balance"].toString();
        cardBalanceString.remove('.');
        qint64 cardBalanceCents = cardBalanceString.toLongLong();

        // Construct window with required parameters
        debitaccountwindow *objDebitAccountWindow = new debitaccountwindow(idAccount, cardBalanceCents);
        objDebitAccountWindow->show();
    }
}
