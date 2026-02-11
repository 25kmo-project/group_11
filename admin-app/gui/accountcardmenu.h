#ifndef ACCOUNTCARDMENU_H
#define ACCOUNTCARDMENU_H

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
#include "cardaccount.h"
#include "account.h"

namespace Ui {
class AccountCardMenu;
}

class AccountCardMenu : public QDialog
{
    Q_OBJECT

public:
    explicit AccountCardMenu(QWidget *parent = nullptr);
    ~AccountCardMenu();

private:
    Ui::AccountCardMenu *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QString customer_base_url;
    QByteArray response_data;
    QVector<Account> cardAccountList;

private slots:
    void btnGetRelationsByIdSlot();
    void showAccountsSlot();
    void relationsToTableSlot(const QVector<Account> &account);
    void btnAddRealtionSlot();
    void btnDeleteRelationSlot();
    void addRelationSlot();
    void deleteRelationSlot();
    void showInfoLabelSlot(QString text);
};

#endif // ACCOUNTCARDMENU_H
