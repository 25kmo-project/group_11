#ifndef CARD_H
#define CARD_H

#include <qjsonobject.h>


class card
{
public:
    QString idCard;
    QString locked;

    static card mapJson(const QJsonObject &json);
};

#endif // CARD_H
