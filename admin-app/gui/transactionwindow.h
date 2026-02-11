#ifndef TRANSACTIONWINDOW_H
#define TRANSACTIONWINDOW_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardItemModel>
#include "environment.h"
#include "authmanager.h"
#include "transaction.h"

namespace Ui {
class transactionwindow;
}

class transactionwindow : public QDialog
{
    Q_OBJECT

public:
    explicit transactionwindow(QWidget *parent = nullptr);
    ~transactionwindow();

private:
    Ui::transactionwindow *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QByteArray response_data;
    QVector<transaction> transactionList;

private slots:
    void btnGetTransactionsSlot();
    void showTransactionsSlot();
    void showInfoLabelSlot(QString text);
    void transactionsToTableSlot(const QVector<transaction> &transaction);
};

#endif // TRANSACTIONWINDOW_H
