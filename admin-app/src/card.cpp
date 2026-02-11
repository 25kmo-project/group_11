#include "card.h"

card card::mapJson(const QJsonObject &json)
{
    card card;
    card.idCard = json["idcard"].toString();
    int loginAttempts = json["login_attempts"].toInt();

    if (loginAttempts == 3) {
        card.locked = "YES";
    } else {
        card.locked = "NO";
    }
    return card;
}

