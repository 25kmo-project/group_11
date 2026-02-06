#include "account.h"

Account Account::mapJson(const QJsonObject &json)
{
    Account account;
    account.idAccount = json["idaccount"].toString().toInt();
    account.balance = json["balance"].toString().toDouble();
    account.accountType = json["account_type"].toString();
    account.creditLimit = json["credit_limit"].toString().toDouble();
    account.idOwner = json["idowner"].toInt();
    return account;
}
