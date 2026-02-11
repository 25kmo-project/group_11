#ifndef ADMINMENU_H
#define ADMINMENU_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "environment.h"
#include "customersmenu.h"
#include "accountsmenu.h"
#include "cardsmenu.h"
#include "accountcardmenu.h"

namespace Ui {
class adminmenu;
}

class adminmenu : public QDialog
{
    Q_OBJECT

public:
    explicit adminmenu(QWidget *parent = nullptr);
    ~adminmenu();

    void setToken(const QByteArray &newToken);

private:
    Ui::adminmenu *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;

private slots:
    void btnCustomersMenuSlot();
    void btnAccountsMenuSlot();
    void btnCardsMenuSlot();
    void btnCardAccountMenuSlot();
};

#endif // ADMINMENU_H
