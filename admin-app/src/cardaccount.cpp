#include "cardaccount.h"

CardAccount CardAccount::mapJson(const QJsonObject &json)
{
    CardAccount cardAccount;
    cardAccount.idAccount = json["account_id"].toString();
    cardAccount.idCard = json["card_id"].toString();
    return cardAccount;
}
