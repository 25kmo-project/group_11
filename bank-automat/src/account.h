#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "../environment.h"
#include "authmanager.h"

class Account : public QObject
{
    Q_OBJECT

public:
    Account(QString idAccount, QObject *parent = nullptr);

    void fetchAccountData();

    QString getIdAccount() const;

    int getIdOwner() const;
    int getBalance() const;
    int getCreditLimit() const;
    QString getAccountType() const;

    void setCreditLimit(int newCreditLimit);
    void setBalance(int newBalance);

    QNetworkReply* balanceAction(double amount, QString actionType);

private:
    QNetworkAccessManager *manager;
    QNetworkReply *reply;

    QString idAccount;
    int idOwner;
    int balance; // Cents
    int creditLimit; // Cents
    QString accountType;

private slots:
    void accountDataSlot();

signals:
    void balanceChanged();
    void accountDataReady();
};

#endif // ACCOUNT_H
