#ifndef ADDCUSTOMERMENU_H
#define ADDCUSTOMERMENU_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>
#include "environment.h"
#include "authmanager.h"

namespace Ui {
class addcustomermenu;
}

class addcustomermenu : public QDialog
{
    Q_OBJECT

public:
    explicit addcustomermenu(QWidget *parent = nullptr);
    ~addcustomermenu();
    QString getCustomerAdd_base_url() const;

private:
    Ui::addcustomermenu *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QByteArray response_data;

private slots:
    void btnGetCustomerData();
    void addCustomerSlot();
    void btnDeleteCustomerSlot();
    void deleteCustomerSlot();
    void showInfoLabelSlot(QString text);
};

#endif // ADDCUSTOMERMENU_H
