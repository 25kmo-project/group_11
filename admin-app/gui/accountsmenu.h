#ifndef ACCOUNTSMENU_H
#define ACCOUNTSMENU_H

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
#include "account.h"
#include "addaccountmenu.h"

namespace Ui {
class accountsmenu;
}

class accountsmenu : public QDialog
{
    Q_OBJECT

public:
    explicit accountsmenu(QWidget *parent = nullptr);
    QString getAccountAdd_base_url() const;
    ~accountsmenu();

private:
    Ui::accountsmenu *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QByteArray response_data;
    QVector<Account> accountList;


private slots:
    void btnGetAccountsSlot();
    void btnGetAccountByIdSlot();
    void btnAddDeleteSlot();
    void showAccountsSlot();
    void accountsToTableSlot(const QVector<Account> &account);
    void showInfoslot(QString info);
};

#endif // ACCOUNTSMENU_H
