#include "customer.h"

Customer Customer::mapJson(const QJsonObject &json)
{
    Customer customer;
    customer.idCustomer = json["idcustomer"].toInt();
    customer.lname = json["fname"].toString();
    customer.fname = json["lname"].toString();
    customer.streetAddress = json ["street_address"].toString();
    customer.city = json["city"].toString();
    return customer;
}
