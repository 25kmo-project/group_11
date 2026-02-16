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

    emit balanceChanged();
    emit accountDataReady();

    reply->deleteLater();
}

QNetworkReply* Account::balanceAction(double amount, QString actionType) {
    QString url = environment::base_url() + "api/account/" + this->idAccount + "/" + actionType;
    QNetworkRequest request(url);
    QByteArray myToken = "Bearer " + AuthManager::instance()->getToken().toUtf8();
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader(QByteArray("Authorization"), (myToken));

    QJsonObject obj;
    if (actionType == "deposit") {
        obj.insert("depositAmount", amount);
        obj.insert("description", "ATM deposit");
    } else if (actionType == "withdraw") {
        obj.insert("withdrawAmount", amount);
        obj.insert("description", "ATM withdraw");
    }
    QJsonDocument jsonDepositDoc(obj);

    return manager->sendCustomRequest(request, "PATCH", jsonDepositDoc.toJson());
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


