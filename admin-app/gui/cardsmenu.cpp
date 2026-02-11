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
    connect(ui->btnGetLockedCards, &QPushButton::clicked, this, &cardsmenu::btnGetLockedCards);
    connect(ui->btnAddDeleteCards, &QPushButton::clicked, this, &cardsmenu::btnAddCardsSlot);
    connect(ui->btnReset, &QPushButton::clicked, this, &cardsmenu::btnResetLockedCardSlot);
    connect(ui->btnDeleteCard, &QPushButton::clicked, this, &cardsmenu::btnDeleteCardSlot);
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

void cardsmenu::btnAddCardsSlot()
{

    QString url = environment::base_url() + cardsmenu::getCard_base_url();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QString id = ui->textCardId_2->text();
    QString pin = ui->textPin->text();

    if (id.length() == 0 or pin.length() == 0) {
        cardsmenu::showInfoslot("Give ID and PIN");
    } else {
        QJsonObject cardObject;
        cardObject.insert("idcard", id);
        cardObject.insert("pin", pin);

        //WEBTOKEN ALKU
        QByteArray myToken="Bearer "+ AuthManager::instance()->getToken().toUtf8();
        request.setRawHeader(QByteArray("Authorization"),(myToken));
        //WEBTOKEN LOPPU

        QJsonDocument cardJsonDoc(cardObject);
        reply = manager->post(request, cardJsonDoc.toJson());
        connect(reply, &QNetworkReply::finished, this, &cardsmenu::addCardSlot);
    }
}

void cardsmenu::btnDeleteCardSlot()
{
    QString id = ui->textDeleteId->text();
    if (id.length() == 0) {
        cardsmenu::showInfoslot("Give ID");
    } else {
        QString url = environment::base_url() + cardsmenu::getCard_base_url() + "/" + id;
        QNetworkRequest request(url);

        //WEBTOKEN ALKU
        QByteArray myToken="Bearer "+ AuthManager::instance()->getToken().toUtf8();
        request.setRawHeader(QByteArray("Authorization"),(myToken));
        //WEBTOKEN LOPPU

        reply = manager->deleteResource(request);
        connect(reply, &QNetworkReply::finished, this, &cardsmenu::deleteCardSlot);
    }
}

void cardsmenu::deleteCardSlot()
{
    response_data = reply->readAll();
    qDebug() << response_data;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(response_data);
    QJsonObject jsonObj = jsonDoc.object();
    QString message = jsonObj.value("message").toString();

    if (response_data.contains("affectedRows")) {
        cardsmenu::showInfoslot("Card deleted");
    } else  if (message.contains("Korttia ei l")){
        cardsmenu::showInfoslot("Card doesn't exist");
    } else {
        cardsmenu::showInfoslot("Delete failed");
    }
    reply -> deleteLater();
}

void cardsmenu::addCardSlot()
{
    response_data = reply->readAll();
    qDebug() << response_data;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(response_data);
    QJsonObject jsonObj = jsonDoc.object();
    QString message = jsonObj.value("message").toString();

    if (response_data.contains("insertId")) {
        cardsmenu::showInfoslot("Card added");
    } else if (message.contains("Ei voi luoda korttia samalla ID")){
        cardsmenu::showInfoslot("ID Already used");
    } else {
        cardsmenu::showInfoslot("Card add failed");
    }
    reply->deleteLater();
}

void cardsmenu::btnGetLockedCards()
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
    connect(reply, &QNetworkReply::finished, this, &cardsmenu::sortLockedCards);
}

void cardsmenu::sortLockedCards()
{
    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "Network error:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray response_data = reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();

    // Clear before made a new array
    cardList.clear();

    for (const QJsonValue &value : json_array) {
        if (value.isObject()) {
            card card = card::mapJson(value.toObject());
            if (card.locked == "YES") {
                cardList.append(card);
            }
        }
    }
    if (cardList.length()== 0) {
        cardsmenu::showInfoslot("No locked cards");
    } else {
        cardsToTableSlot(cardList);
    }
}

void cardsmenu::btnResetLockedCardSlot()
{
    // Set url + header
    QString id = ui->textResetId->text();
    if (id.length() == 0){
        cardsmenu::showInfoslot("Give ID");
    } else {
        QString url = environment::base_url() + "api/login/" + id + "/reset";
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QJsonObject cardToReset;
        cardToReset.insert("idcard", id);

        // WEB TOKEN ALKU
        QByteArray myToken = "Bearer " + AuthManager::instance()->getToken().toUtf8();
        request.setRawHeader(QByteArray("Authorization"),(myToken));
        // WEB TOKEN LOPPU

        QJsonDocument cardJsonDoc(cardToReset);
        reply = manager->post(request, cardJsonDoc.toJson());
        connect(reply, &QNetworkReply::finished, this, &cardsmenu::resetCardSlot);
    }
}

void cardsmenu::resetCardSlot()
{
    response_data = reply->readAll();
    qDebug() << response_data;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(response_data);
    QJsonObject jsonObj = jsonDoc.object();
    QString message = jsonObj.value("message").toString();

    if (message.contains("Korttia ei l")) {
        cardsmenu::showInfoslot("Card doesn't exist");
    } else if (message.contains("Kirjautumisyritykset resetoitu")){
        cardsmenu::showInfoslot("Reset done");
    } else {
        cardsmenu::showInfoslot("Reset failed");
    }
    reply->deleteLater();
}

void cardsmenu::showCardsSlot()
{
    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "Network error:" << reply->errorString();
        reply->deleteLater();
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
