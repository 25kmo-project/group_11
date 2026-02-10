#ifndef CARDDEPOSITWINDOW_H
#define CARDDEPOSITWINDOW_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>
#include "../environment.h"
#include "../mainwindow.h"
#include "../src/account.h"
#include "../src/authmanager.h"

namespace Ui {
class CardDepositWindow;
}

class CardDepositWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CardDepositWindow(
        Account *newAccount,
        QWidget *parent = nullptr
        );
    ~CardDepositWindow();
    QNetworkAccessManager *manager;
    QNetworkReply *reply;

private:
    Ui::CardDepositWindow *ui;
    Account *account;

private slots:
    void btnDepositSlot();
    void depositActionSlot();
    void showLabelErrorSlot(QString text);
    void cancelDepositSlot();

signals:
    void infoMessage(const QString &text);
};

#endif // CARDDEPOSITWINDOW_H
