#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "../environment.h"
#include "authmanager.h"

class Customer : public QObject
{
    Q_OBJECT

public:
    Customer(int idOwner, QObject *parent = nullptr);

    void fetchCustomerData();

    int getIdOwner() const;
    QString getFname() const;
    QString getLname() const;
    QString getStreetAddress() const;
    QString getCity() const;

private:
    QNetworkAccessManager *manager;
    QNetworkReply *reply;

    int idOwner;
    QString fname;
    QString lname;
    QString streetAddress;
    QString city;

signals:
    void customerDataReady();

private slots:
    void CustomerDataSlot();
};

#endif // CUSTOMER_H
