#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <qjsonobject.h>

class Customer
{
public:
    int idCustomer;
    QString fname;
    QString lname;
    QString streetAddress;
    QString city;

    static Customer mapJson(const QJsonObject &json);
};

#endif // CUSTOMER_H
