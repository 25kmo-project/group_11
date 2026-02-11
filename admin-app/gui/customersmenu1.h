#ifndef CUSTOMERSMENU1_H
#define CUSTOMERSMENU1_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


namespace Ui {
class customersmenu;
}

class customersmenu : public QDialog
{
    Q_OBJECT

public:
    explicit customersmenu(QWidget *parent = nullptr);
    ~customersmenu();

private:
    Ui::customersmenu *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;

private slots:
    void btnGetCustomers();
    // void tableCustomers();
};

#endif // CUSTOMERS_H
