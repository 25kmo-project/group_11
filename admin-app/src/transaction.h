#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <QDateTime>
#include <QJsonObject>

class transaction
{
public:
    int idTransaction;
    QString idAccount;
    qint64 amountCents;
    QDateTime date;
    QString description;

    static transaction mapJson(const QJsonObject &json);
};

#endif // TRANSACTION_H
