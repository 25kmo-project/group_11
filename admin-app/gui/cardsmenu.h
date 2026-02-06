#ifndef CARDSMENU_H
#define CARDSMENU_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardItemModel>
#include <QTimer>
#include "environment.h"
#include "authmanager.h"
#include "card.h"

namespace Ui {
class cardsmenu;
}

class cardsmenu : public QDialog
{
    Q_OBJECT

public:
    explicit cardsmenu(QWidget *parent = nullptr);
    ~cardsmenu();

    QString getCard_base_url() const;

private:
    Ui::cardsmenu *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QString customer_base_url;
    QByteArray response_data;
    QVector<card> cardList;

private slots:
    void btnGetAllCardsSlot();
    void btnGetCardByIdSlot();
    void btnAddDeleteCardsSlot();
    void showCardsSlot();
    void cardsToTableSlot(const QVector<card> &cards);
    void showInfoslot(QString info);

};

#endif // CARDSMENU_H
