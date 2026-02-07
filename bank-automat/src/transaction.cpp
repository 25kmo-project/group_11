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

    qDebug() << "Transaction ID " << t.id;
    qDebug() << "Transaction account id " <<t.account_id;
    qDebug() << "Transaction ammount" << t.amount;
    qDebug() << "Transaction date " << t.date;
    qDebug() << "Transaction desc " << t.description;

    return t;
}
