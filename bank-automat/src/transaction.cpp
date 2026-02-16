#include "transaction.h"

Transaction Transaction::fromJson(const QJsonObject& obj) {
    Transaction t;
    t.id = obj.value("idtransaction").toInt();
    t.account_id = obj.value("idaccount").toInt();
    t.amount = obj.value("amount").toString().toDouble();

    t.date = QDateTime::fromString(
        obj.value("date").toString(),
        Qt::ISODate
        );

    t.description = obj.value("description").toString();

    return t;
}
