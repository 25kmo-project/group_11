#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "environment.h"
#include "src/authmanager.h"
#include "gui/accountview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnLogin, &QPushButton::clicked, this, &MainWindow::btnLoginSlot);
    connect(ui->btnDebit, &QPushButton::clicked, this, &MainWindow::chooseAccountSlot);
    connect(ui->btnCredit, &QPushButton::clicked, this, &MainWindow::chooseAccountSlot);
    connect(ui->btnLogout, &QPushButton::clicked, this, &MainWindow::logoutSlot);
    manager = new QNetworkAccessManager(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btnLoginSlot()
{
    // Check that the ID and PIN code fields are not empty
    if (ui->textCardId->text() == "" || ui->textPin->text() == "") {
        showError("Card ID or PIN code cannot be empty.");
        return;
    }

    // Set request url and header
    QString url = environment::base_url() + "api/login/";
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Create object, where to insert idcard and pin
    QJsonObject loginObject;
    loginObject.insert("idcard", ui->textCardId->text());
    loginObject.insert("pin", ui->textPin->text());

    // Clear line edits
    ui->textCardId->clear();
    ui->textPin->clear();

    // Create QJsonDocument and post request
    QJsonDocument jsonLoginDoc(loginObject);
    reply = manager->post(request, jsonLoginDoc.toJson());
    connect(reply, &QNetworkReply::finished, this, &MainWindow::loginActionSlot);
}

void MainWindow::loginActionSlot()
{
    // Check for errors
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << statusCode;
    switch (statusCode) {
        case 0:
            showError("Connection error, try again later.");
            return;
            break;
        case 403:
            showError("Too many failed login attemps, card has been locked.");
            return;
            break;
        case 404:
            showError("ID and PIN do not match any cards.");
            return;
            break;
        case 500:
            showError("A server error has occurred, try again later.");
            return;
            break;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObject = jsonDoc.object();

    // If responseData have token -> Login is successful
    if (jsonObject.contains("token")) {
        // Type conversion
        QString token = jsonObject["token"].toString();
        QByteArray tokenBytes = token.toUtf8();
        QByteArray idcard = jsonObject["idcard"].toString().toUtf8();

        // Set token to AuthManager to usable easier elsewhere
        AuthManager::instance()->setToken(tokenBytes);

        // URL to get card accounts
        QString url = environment::base_url() + "api/card/" + idcard + "/accounts/";
        QNetworkRequest request(url);

        //WEB TOKEN START
        QByteArray myToken = "Bearer " + AuthManager::instance()->getToken().toUtf8();
        request.setRawHeader(QByteArray("Authorization"),(myToken));
        //WEB TOKEN END

        reply = manager->get(request);
        connect(reply, &QNetworkReply::finished, this, &MainWindow::handleAccountsResponse);
    } else {
        showError("Something went wrong.");
    }
}

void MainWindow::handleAccountsResponse()
{
    QByteArray responseData = reply->readAll();
    QJsonDocument jsonCardDoc = QJsonDocument::fromJson(responseData);
    QJsonArray cardAccounts = jsonCardDoc.array();

    // If no accounts -> Show noAccountView
    if (cardAccounts.size() == 0) {
        ui->stackedWidget->setCurrentIndex(1);
        ui->frameAccounts->hide();
        ui->lblNoAccounts->show();
        return;
    }

    for (const auto &account : cardAccounts) {
        QJsonObject obj = account.toObject();

        // Insert values into QMap (resembles JSON), where the key is the account type and the value for the key is the account's ID
        this->accounts.insert(obj["account_type"].toString(), obj["idaccount"].toString());
    }

    if (cardAccounts.size() == 1) {
        // Get first value from accounts and create AccountView with it
        QString key = this->accounts.firstKey();
        AccountView *objAccountView = new AccountView(this->accounts.value(key), this);
        objAccountView->show();
    } else if (cardAccounts.size() == 2) {
        // If card has two accounts, change to card selection page (index 1)
        ui->stackedWidget->setCurrentIndex(1);
        ui->lblNoAccounts->hide();
        ui->frameAccounts->show();
    }

    reply->deleteLater();
}

void MainWindow::chooseAccountSlot() {
    QString buttonAccountType = sender()->property("accountType").toString();

    AccountView *objAccountView = new AccountView(this->accounts.value(buttonAccountType), this);
    objAccountView->show();

    // After AccountView has been created with selected account, clear QMap and return MainWindow back to login screen
    this->accounts.clear();
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::logoutSlot() {
    AuthManager::instance()->clearToken();
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::showError(QString message) {
    ui->labelError->setText(message);
    ui->labelError->show();

    //Timer for labelError
    QTimer::singleShot(4000, this, [this]() {
        ui->labelError->clear();
    });
}
