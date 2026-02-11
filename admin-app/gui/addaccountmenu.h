#ifndef ADDACCOUNTMENU_H
#define ADDACCOUNTMENU_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>

#include "authmanager.h"
#include "environment.h"


namespace Ui {
class addaccountmenu;
}

class addaccountmenu : public QDialog
{
    Q_OBJECT

public:
    explicit addaccountmenu(QWidget *parent = nullptr);
    ~addaccountmenu();
    QString getAccountAdd_base_url() const;


private:
    Ui::addaccountmenu *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QByteArray response_data;

private slots:
    void btnGetAccountDataSlot();
    void addAccountSlot();
    void btnDeleteAccountSlot();
    void deleteAccountSlot();
    void showInfoLabelSlot(QString text);
};


#endif // ADDACCOUNTMENU_H
