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
    reply= manager->post(request, jsonLoginDoc.toJson());
    connect(reply, &QNetworkReply::finished, this, &MainWindow::loginActionSlot);
}

void MainWindow::loginActionSlot()
{
    QByteArray responseData = reply->readAll();

    // Check are backend up
    if (reply->error() != QNetworkReply::NoError) {
        qDebug()<< "Check backend";
        ui->labelInfo->setText("Yhteysvirhe");
        ui->labelInfo->show();

        //Timer for labelInfo
        QTimer::singleShot(4000, this, [this]() {
            ui->labelInfo->clear();
        });
    }

    // If cardID or PIN is empty
    if (responseData.length()==1) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject = jsonDoc.object();
        ui->labelInfo->setText(jsonObject.value("message").toString());
        ui->labelInfo->show();

        //Timer for labelInfo
        QTimer::singleShot(4000, this, [this]() {
            ui->labelInfo->clear();
        });

    // If backend is up, then check CardID & PIN
    } else {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject = jsonDoc.object();

        // If card locked
        if(jsonObject.value("message").toString()== "Liian monta kirjautumisyritystä, tunnus on lukittu.") {
            MainWindow::showInfoLabelSlot("Card locked");
        }

        // If PIN or Idcard doesnt have input or do not match
        else if (!jsonObject.contains("token")) {
            MainWindow::showInfoLabelSlot("ID card and PIN do not match.");
        }

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
        }
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


void MainWindow::showInfoLabelSlot(QString text)
{
    ui->labelInfo->setText(text);
    QTimer::singleShot(4000,this,[this]() {
        ui->labelInfo->clear();
    });
}

