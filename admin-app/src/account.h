#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <qjsonobject.h>

class Account
{
public:
    int idAccount;
    QString accountType;
    double balance;
    double creditLimit;
    int idOwner;

    static Account mapJson(const QJsonObject &json);
};

#endif // ACCOUNT_H
