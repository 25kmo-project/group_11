#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "environment.h"
#include "src/authmanager.h"
#include "src/account.h"
#include "gui/noaccountsview.h"
#include "gui/accountview.h"
#include "gui/cardselectiondialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnLogin, &QPushButton::clicked, this, &MainWindow::btnLoginSlot);
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
        ui->labelError->setText(QString("Card ID or PIN code cannot be empty."));
        ui->labelError->show();

        //Timer for labelError
        QTimer::singleShot(4000, this, [this]() {
            ui->labelError->clear();
        });

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

    // Account is a QObject so a pointer is needed since QObjects cannot be moved or copied
    QVector<Account*> accounts;

    // If no accounts -> Show noAccountView
    if (cardAccounts.size() == 0) {
        noaccountsview *objNoAccountsView = new noaccountsview(this);
        objNoAccountsView->show();
    } else {
        // Create every account account-class and add it to accounts QVector
        for (const auto &account : cardAccounts) {
            QJsonObject obj = account.toObject();

            QString idAccount = obj["idaccount"].toString();
            Account *acc = new Account(idAccount, this);

            // Add account to accounts to QVecotr
            accounts.append(acc);
        }
        // If two accounts -> Then selecting view
        if (accounts.size() == 2){
            cardselectiondialog *objCardSelectionView = new cardselectiondialog(accounts,this);
            objCardSelectionView->show();
        // If one account -> Open accountview
        } else {
            AccountView *objAccountView = new AccountView(accounts[0], this);
            objAccountView->show();
        }

    reply->deleteLater();
    }
}

void MainWindow::showError(QString message) {
    ui->labelError->setText(message);
    ui->labelError->show();

    //Timer for labelError
    QTimer::singleShot(4000, this, [this]() {
        ui->labelError->clear();
    });
}
