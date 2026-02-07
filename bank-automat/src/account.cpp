#include "account.h"

Account::Account(const QString newIdAccount, QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    this->idAccount = newIdAccount;
    this->fetchAccountData();
}

void Account::fetchAccountData() {
    QString url = environment::base_url() + "api/account/" + this->idAccount;
    QNetworkRequest request(url);
    QByteArray myToken = "Bearer " + AuthManager::instance()->getToken().toUtf8();
    request.setRawHeader(QByteArray("Authorization"),(myToken));

    reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &Account::accountDataSlot);
}

void Account::accountDataSlot() {
    QByteArray response = reply->readAll();

    QJsonDocument jsonCardDoc = QJsonDocument::fromJson(response);
    QJsonArray account = jsonCardDoc.array();
    QJsonObject obj = account[0].toObject();

    QString balanceStr = obj["balance"].toString();
    balanceStr.remove(".");
    qint64 newBalance = balanceStr.toLongLong();

    QString creditStr = obj["credit_limit"].toString();
    creditStr.remove(".");
    qint64 newCreditLimit = creditStr.toLongLong();

    this->balance = newBalance;
    this->creditLimit = newCreditLimit;
    this->accountType = obj["account_type"].toString();
    this->idOwner = obj["idowner"].toInt();

    reply->deleteLater();
}

QString Account::getIdAccount() const
{
    return idAccount;
}

int Account::getIdOwner() const
{
    return idOwner;
}

int Account::getBalance() const
{
    return balance;
}

QString Account::getAccountType() const
{
    return accountType;
}

int Account::getCreditLimit() const
{
    return creditLimit;
}

void Account::setBalance(int newBalance)
{
    balance = newBalance;
}

void Account::setCreditLimit(int newCreditLimit)
{
    creditLimit = newCreditLimit;
}


