#ifndef CUSTOMERSMENU_H
#define CUSTOMERSMENU_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardItemModel>
#include "environment.h"
#include "customer.h"
#include "addcustomermenu.h"
#include "authmanager.h"


namespace Ui {
class customersmenu;
}

class customersmenu : public QDialog
{
    Q_OBJECT

public:
    explicit customersmenu(QWidget *parent = nullptr);
    ~customersmenu();

    QString getCustomer_base_url() const;

private:
    Ui::customersmenu *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QString customer_base_url;
    QByteArray response_data;
    QVector<Customer> customerList;

private slots:
    void btnGetCustomers();
    void btnGetCustomerByIdSlot();
    void showCustomerSlot();
    void customersToTableSlot(const QVector<Customer> &customers);
    void btnAddNewCustomerMenuSlot();
    void showInfoslot(QString info);
};

#endif // CUSTOMERSMENU_H
