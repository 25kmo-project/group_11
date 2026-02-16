#include "customer.h"

Customer::Customer(int idOwner, QObject *parent)
{
    manager = new QNetworkAccessManager(this);
    this->idOwner = idOwner;
    this->fetchCustomerData();
}

void Customer::fetchCustomerData()
{
    QString url = environment::base_url() + "api/customer/" + QString::number(this->idOwner);
    QNetworkRequest request(url);
    QByteArray myToken = "Bearer " + AuthManager::instance()->getToken().toUtf8();
    request.setRawHeader(QByteArray("Authorization"), (myToken));

    reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &Customer::CustomerDataSlot);
}

void Customer::CustomerDataSlot()
{
    QByteArray responseData = reply->readAll();

    QJsonDocument jsonCustomerDoc = QJsonDocument::fromJson(responseData);
    QJsonArray customer = jsonCustomerDoc.array();
    QJsonObject objCustomer = customer[0].toObject();

    QString fname = objCustomer["fname"].toString();
    QString lname = objCustomer["lname"].toString();
    QString streetAddress = objCustomer["street_address"].toString();
    QString city = objCustomer["city"].toString();

    this->fname = fname;
    this->lname = lname;
    this->streetAddress = streetAddress;
    this->city = city;

    emit customerDataReady();

    reply->deleteLater();
}

int Customer::getIdOwner() const
{
    return idOwner;
}

QString Customer::getFname() const
{
    return fname;
}

QString Customer::getLname() const
{
    return lname;
}

QString Customer::getStreetAddress() const
{
    return streetAddress;
}

QString Customer::getCity() const
{
    return city;
}


