#ifndef CARDACCOUNT_H
#define CARDACCOUNT_H

#include <qjsonobject.h>

class CardAccount
{
public:
    QString idCard;
    QString idAccount;

    static CardAccount mapJson(const QJsonObject &json);
};

#endif // CARDACCOUNT_H
