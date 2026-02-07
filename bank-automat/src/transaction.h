#pragma once

#include <QString>
#include <QDateTime>
#include <QJsonObject>

struct Transaction {
    int id = 0;
    int account_id = 0;
    double amount = 0.0;
    QDateTime date;
    QString description;

    static Transaction fromJson(const QJsonObject& obj);
};
