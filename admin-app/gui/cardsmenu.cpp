#include "cardsmenu.h"
#include "ui_cardsmenu.h"



cardsmenu::cardsmenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cardsmenu)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    connect(ui->btnGetAllCards, &QPushButton::clicked, this, &cardsmenu::btnGetAllCardsSlot);
    connect(ui->btnGetCardById, &QPushButton::clicked, this, &cardsmenu::btnGetCardByIdSlot);
    connect(ui->btnAddDeleteCards, &QPushButton::clicked, this, &cardsmenu::btnAddDeleteCardsSlot);
}

cardsmenu::~cardsmenu()
{
    delete ui;
}

QString cardsmenu::getCard_base_url() const
{
    return "api/card";
}

void cardsmenu::btnGetAllCardsSlot()
{
    // Set url + header
    QString url = environment::base_url() + cardsmenu::getCard_base_url();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // WEB TOKEN ALKU
    QByteArray myToken = "Bearer " + AuthManager::instance()->getToken().toUtf8();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    // WEB TOKEN LOPPU

    reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &cardsmenu::showCardsSlot);
}

void cardsmenu::btnGetCardByIdSlot()
{
    // Set url + header
    QString id = ui->textCardId->text();
    if (id.length() == 0) {
        cardsmenu::showInfoslot("Give card ID");
    } else {
        QString url = environment::base_url() + cardsmenu::getCard_base_url() + "/" + id;
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        // WEB TOKEN ALKU
        QByteArray myToken = "Bearer " + AuthManager::instance()->getToken().toUtf8();
        request.setRawHeader(QByteArray("Authorization"),(myToken));
        // WEB TOKEN LOPPU

        reply = manager->get(request);
        connect(reply, &QNetworkReply::finished, this, &cardsmenu::showCardsSlot);
    }
}

void cardsmenu::btnAddDeleteCardsSlot()
{
    /*
    QString id = ui->textCustomerId->text();
    QString url = environment::base_url() + addcustomermenu::getCustomerAdd_base_url() + "/" + id;
    QNetworkRequest request(url);

    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+ AuthManager::instance()->getToken().toUtf8();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    reply = manager->deleteResource(request);
    connect(reply, &QNetworkReply::finished, this, &addcustomermenu::deleteCustomerSlot);
    */
}

void cardsmenu::showCardsSlot()
{
    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "Network error:" << reply->errorString();
        reply->deleteLater();
        manager->deleteLater();
        return;
    }

    QByteArray response_data = reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();

    // Clear before made a new array
    cardList.clear();

    // Make a array from cards
    for (const QJsonValue &value : json_array) {
        if (value.isObject()) {
            card card = card::mapJson(value.toObject());
            cardList.append(card);
        }
    }
    cardsToTableSlot(cardList);
}

void cardsmenu::cardsToTableSlot(const QVector<card> &cards)
{
    auto *tableModel = new QStandardItemModel(cards.size(), 2, this);
    tableModel -> setHorizontalHeaderLabels({ tr("Card ID"), tr("Locked") });

    for (int row = 0; row < cards.size(); ++row) {
        const card &handlingCard = cards[row];
        tableModel->setItem(row, 0, new QStandardItem(handlingCard.idCard));
        tableModel->setItem(row, 1, new QStandardItem(handlingCard.locked));
    }
    ui->tableCards->setModel(tableModel);
    ui->tableCards->verticalHeader()->setVisible(false);
    ui->tableCards->resizeColumnsToContents();
    ui->tableCards->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    if (cards.size() == 0) {
        cardsmenu::showInfoslot("ID doesn't exist");
    }
}

void cardsmenu::showInfoslot(QString info)
{
    ui->labelInfo->setText(info);

    QTimer::singleShot(4000,this,[this]() {
        ui->labelInfo->clear();
    });
}
