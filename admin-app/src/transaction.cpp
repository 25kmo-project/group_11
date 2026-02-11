#include "transaction.h"

transaction transaction::mapJson(const QJsonObject &json)
{
    transaction transaction;

    transaction.idTransaction = json["idtransaction"].toInt();
    transaction.idAccount = json["idaccount"].toString();

    double amountDouble = json["amount"].toString().toDouble();
    transaction.amountCents = qRound64(amountDouble * 100.0);

    transaction.date = QDateTime::fromString(json["date"].toString(),Qt::ISODate);
    transaction.description = json["description"].toString();

    return transaction;
}
