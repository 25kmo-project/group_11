#include "accountcardmenu.h"
#include "ui_accountcardmenu.h"

#include <QTimer>

AccountCardMenu::AccountCardMenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AccountCardMenu)
{
    ui->setupUi(this);
    connect(ui->btnGetOneRelationById, &QPushButton::clicked, this, &AccountCardMenu::btnGetRelationsByIdSlot);
    connect(ui->btnAddRelation, &QPushButton::clicked, this, &AccountCardMenu::btnAddRealtionSlot);
    connect(ui->btnDeleteRelation, &QPushButton::clicked, this, &AccountCardMenu::btnDeleteRelationSlot);
    manager = new QNetworkAccessManager(this);
}

AccountCardMenu::~AccountCardMenu()
{
    delete ui;
}

void AccountCardMenu::btnGetRelationsByIdSlot()
{
    QString id = ui->textCardIdToShow->text();
    if (id == "") {
        AccountCardMenu::showInfoLabelSlot("Give ID");
    } else {
        // Set url + header
        QString url = environment::base_url() + "api/card/" + id + "/accounts";
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        // WEB TOKEN ALKU
        QByteArray myToken = "Bearer " + AuthManager::instance()->getToken().toUtf8();
        request.setRawHeader(QByteArray("Authorization"),(myToken));
        // WEB TOKEN LOPPU

        reply = manager->get(request);
        connect(reply, &QNetworkReply::finished, this, &AccountCardMenu::showAccountsSlot);
    }
}

void AccountCardMenu::showAccountsSlot()
{
    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "Network error:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray response_data = reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();

    cardAccountList.clear();

    for (const QJsonValue &value : json_array) {
        if (value.isObject()) {
            Account account = Account::mapJson(value.toObject());
            // qDebug() << "Account type: " << account.accountType << " Balance: " << account.balance;
            cardAccountList.append(account);
        }
    }
    relationsToTableSlot(cardAccountList);
}

void AccountCardMenu::relationsToTableSlot(const QVector<Account> &account)
{
    auto *tableModel = new QStandardItemModel(account.size(), 5, this);
    tableModel -> setHorizontalHeaderLabels({tr("AccountID"), tr("AccountType"), tr("Balance"), tr("CreditLimit"), tr("OwnerID")});

    for (int row = 0; row < account.size(); row++) {
        const Account &handlingAccount = account[row];
        tableModel->setItem(row, 0, new QStandardItem(QString::number(handlingAccount.idAccount)));
        tableModel->setItem(row, 1, new QStandardItem(handlingAccount.accountType));
        tableModel->setItem(row, 2, new QStandardItem(QString::number(handlingAccount.balance)));
        tableModel->setItem(row, 3, new QStandardItem(QString::number(handlingAccount.creditLimit)));
        tableModel->setItem(row, 4, new QStandardItem(QString::number(handlingAccount.idOwner)));
    }
    ui->tableCardAccounts->setModel(tableModel);
    ui->tableCardAccounts->verticalHeader()->setVisible(false);
    ui->tableCardAccounts->resizeColumnsToContents();
    ui->tableCardAccounts->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    if (account.size() == 0) {
        AccountCardMenu::showInfoLabelSlot("Given card doesn't have accounts");
    }
    reply -> deleteLater();
}

void AccountCardMenu::btnAddRealtionSlot()
{
    QString url = environment::base_url() + "api/card_account/accounttocard";
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QString idCard = ui->textCardIdToDelete->text();
    QString idAccount = ui->textAccountIdToDelete->text();

    if (idCard.isEmpty() || idAccount.isEmpty()) {
        AccountCardMenu::showInfoLabelSlot("Give both ID's");
    } else {
        QJsonObject accountToAddObj;
        accountToAddObj.insert("idcard", idCard);
        accountToAddObj.insert("idaccount", idAccount);

        // WEB TOKEN ALKU
        QByteArray myToken = "Bearer " + AuthManager::instance()->getToken().toUtf8();
        request.setRawHeader(QByteArray("Authorization"),(myToken));
        // WEB TOKEN LOPPU

        QJsonDocument accountToAddDoc(accountToAddObj);
        reply = manager->post(request, accountToAddDoc.toJson());
        connect(reply, &QNetworkReply::finished, this, &AccountCardMenu::addRelationSlot);
    }
}

void AccountCardMenu::btnDeleteRelationSlot()
{
    QString url = environment::base_url() + "api/card_account/removeaccountfromcard";
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QString idCard = ui->textCardIdToDelete->text();
    QString idAccount = ui->textAccountIdToDelete->text();

    if (idCard.isEmpty() || idAccount.isEmpty()) {
        AccountCardMenu::showInfoLabelSlot("Give both ID's");
    } else {
        qDebug() << "testi";
        QJsonObject accountToDeleteObj;
        accountToDeleteObj.insert("idcard", idCard);
        accountToDeleteObj.insert("idaccount", idAccount);

        // WEB TOKEN ALKU
        QByteArray myToken = "Bearer " + AuthManager::instance()->getToken().toUtf8();
        request.setRawHeader(QByteArray("Authorization"),(myToken));
        // WEB TOKEN LOPPU

        QJsonDocument accountToDeleteDoc(accountToDeleteObj);
        reply = manager->sendCustomRequest(request, "DELETE", accountToDeleteDoc.toJson());
        connect(reply, &QNetworkReply::finished, this, &AccountCardMenu::deleteRelationSlot);
    }
}

void AccountCardMenu::addRelationSlot()
{
    response_data = reply->readAll();
    qDebug() << response_data;
    QJsonDocument docReply = QJsonDocument::fromJson(response_data);
    QJsonObject objReply = docReply.object();
    QString message = objReply.value("message").toString();

    if (message.contains("Antamaasi tilia ei olemassa")) {
        AccountCardMenu::showInfoLabelSlot("Given account doesn't exist");
    }
    if (message.contains("Tili lisatty onnistuneesti")) {
        AccountCardMenu::showInfoLabelSlot("Account added succesfully");
    }
    if (message.contains("Kortilla on jo lis")) {
        AccountCardMenu::showInfoLabelSlot("Card has already adding account type");
    }
    if (message.contains("Tili ja kortti liitetty")) {
        AccountCardMenu::showInfoLabelSlot("Account added succesfully");
    }
    if (message.contains("Kortilla on jo DEBIT ja CREDIT ")) {
        AccountCardMenu::showInfoLabelSlot("Card has both DEBIT and CREDIT accounts");
    }
    reply -> deleteLater();
}

void AccountCardMenu::deleteRelationSlot()
{
    response_data = reply->readAll();
    qDebug() << response_data;
    QJsonDocument docReply = QJsonDocument::fromJson(response_data);
    QJsonObject objReply = docReply.object();
    QString message = objReply.value("message").toString();

    if (message.contains("Antamaasi tilia ei olemassa")) {
        AccountCardMenu::showInfoLabelSlot("Given account doesn't exist");
    }
    if (message.contains("Annetulla kortilla ei ole kyse")) {
        AccountCardMenu::showInfoLabelSlot("Card doesn't have given account");
    }
    if (message.contains("Tilin ja kortin liitos poistettu")) {
        AccountCardMenu::showInfoLabelSlot("Account deleted from given card");
    }
    if (message.contains("Annetulla kortilla ei ole til")) {
        AccountCardMenu::showInfoLabelSlot("Given card doesn't have accounts");
    }
    reply -> deleteLater();
}

void AccountCardMenu::showInfoLabelSlot(QString text)
{
    ui->labelInfo->setText(text);
    QTimer::singleShot(4000,this,[this]() {
        ui->labelInfo->clear();
    });
}
