#include "addaccountmenu.h"
#include "ui_addaccountmenu.h"



addaccountmenu::addaccountmenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addaccountmenu)
{
    ui->setupUi(this);
    ui->comboAccountType->addItem("DEBIT");
    ui->comboAccountType->addItem("CREDIT");
    manager = new QNetworkAccessManager(this);
    connect(ui->btnAddAccount, &QPushButton::clicked, this, &addaccountmenu::btnGetAccountDataSlot);
    connect(ui->btnDeleteAccount, &QPushButton::clicked, this, &addaccountmenu::btnDeleteAccountSlot);
}

addaccountmenu::~addaccountmenu()
{
    delete ui;
}

QString addaccountmenu::getAccountAdd_base_url() const
{
    return "api/account";
}

void addaccountmenu::btnGetAccountDataSlot()
{
    // Set url + header
    QString url = environment::base_url() + addaccountmenu::getAccountAdd_base_url();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Read needed parameters
    QString idAccount = ui->textAddAccountId->text();
    double balanceDouble = ui->textBalance->text().toDouble();
    QString accountType = ui->comboAccountType->currentText();
    double creditLimitDouble = ui->textCreditLimit->text().toDouble();
    int idOwner = ui->textOwnerId->text().toInt();

    // If debit, then set creditlimit to 0
    if (accountType == "DEBIT") {
        creditLimitDouble = 0;
    }

    // Parameter type configuration
    QString balanceStr = QString::number(balanceDouble, 'f', 2);
    QString creditLimitStr = QString::number(creditLimitDouble, 'f', 2);

    // Set parameters to object which to post
    QJsonObject account;
    account.insert("idaccount", idAccount);
    account.insert("balance", balanceStr);
    account.insert("account_type", accountType);
    account.insert("credit_limit", creditLimitStr);
    account.insert("idowner", idOwner);

    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+ AuthManager::instance()->getToken().toUtf8();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    // Object to JsonDocument + post
    QJsonDocument accountJsonDoc(account);
    reply = manager->post(request, accountJsonDoc.toJson());
    connect(reply, &QNetworkReply::finished, this, &addaccountmenu::addAccountSlot);
}

void addaccountmenu::addAccountSlot()
{
    response_data = reply->readAll();

    // If account has created succesfully
    if (response_data.contains("affectedRows")) {
        addaccountmenu::showInfoLabelSlot("Account added succesfully");

    // If account hasn't created succesfully
    } else {
        QJsonDocument doc = QJsonDocument::fromJson(response_data);
        QJsonObject obj = doc.object();
        int statusCode = obj["status_code"].toInt();
        if (statusCode == 400) {
            addaccountmenu::showInfoLabelSlot("ID already used");
        } else if (statusCode == 404) {
            addaccountmenu::showInfoLabelSlot("Owner ID doesn't exsist");
        } else {
            addaccountmenu::showInfoLabelSlot("Error: Unknown");
        }
    }
    reply->deleteLater();
}



void addaccountmenu::btnDeleteAccountSlot()
{
    //Set url and header
    QString idToDelete = ui->textDeleteAccountId->text();

    QString url = environment::base_url() + addaccountmenu::getAccountAdd_base_url() + "/" + idToDelete;
    QNetworkRequest request (url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+ AuthManager::instance()->getToken().toUtf8();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    reply = manager ->deleteResource(request);
    connect(reply, &QNetworkReply::finished, this, &addaccountmenu::deleteAccountSlot);
}

void addaccountmenu::deleteAccountSlot()
{
    response_data = reply->readAll();

    if (response_data.contains("affectedRows")) {
        addaccountmenu::showInfoLabelSlot("Account deleted");
    } else {
        addaccountmenu::showInfoLabelSlot("Delete failed");
    }
    reply -> deleteLater();
}

void addaccountmenu::showInfoLabelSlot(QString text)
{
    ui->labelInfo->setText(text);

    QTimer::singleShot(4000,this,[this]() {
        ui->labelInfo->clear();
    });
}

