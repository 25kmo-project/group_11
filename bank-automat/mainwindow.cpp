#include "mainwindow.h"
#include "./ui_mainwindow.h"

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
    QString url = environment::base_url() + "api/login/";
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject loginObject;
    loginObject.insert("idcard", ui->textCardId->text());
    loginObject.insert("pin", ui->textPin->text());

    // Clear line edits
    ui->textCardId->clear();
    ui->textPin->clear();

    QJsonDocument jsonLoginDoc(loginObject);
    reply= manager->post(request, jsonLoginDoc.toJson());
    connect(reply, &QNetworkReply::finished, this, &MainWindow::loginActionSlot);
}

void MainWindow::loginActionSlot()
{
    QByteArray responseData = reply->readAll();

    // Check are backend up
    if (reply->error() != QNetworkReply::NoError) {
        qDebug()<< "Tarkista backend";
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
            ui->labelInfo->setText("Tunnus lukittu");
            ui->labelInfo->show();

            //Timer for labelInfo
            QTimer::singleShot(4000, this, [this]() {
                ui->labelInfo->clear();
            });
        }

        // If PIN or Idcard doesnt have input or do not match
        else if (!jsonObject.contains("token")) {
            ui->labelInfo->setText("Idcard ja PIN eivät täsmää.");
            ui->labelInfo->show();

            // Timer for labelInfo
            QTimer::singleShot(4000, this, [this]() {
                ui->labelInfo->clear();
            });
        }

        // If responseData have token -> Login is successful
        if (jsonObject.contains("token")) {
            // Type conversion
            token = jsonObject["token"].toString().toUtf8();;
            idcard = jsonObject["idcard"].toString().toUtf8();;

            // URL to get card accounts
            QString url = environment::base_url() + "api/card/" + idcard + "/accounts/";
            QNetworkRequest request(url);
            //WEB TOKEN START
            QByteArray myToken = "Bearer " + token;
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

    // Tuloste debuggausta varten
    /*
    qDebug().noquote() << responseData;
    qDebug() << "Accounts: " << cardAccounts.size();
    */

    if (cardAccounts.size() == 0) {
        qDebug() << "Accounts: 0";
        noaccountsview *objNoAccountsView = new noaccountsview(this);
        objNoAccountsView->show();
    } else if (cardAccounts.size() == 1) {
        QJsonObject objCard = cardAccounts.at(0).toObject();

        if (objCard["account_type"].toString() == "DEBIT") {
            // Data handling to construct debitaccountwindow
            QString idAccount = objCard["idaccount"].toString();

            QString cardBalanceString = objCard["balance"].toString();
            cardBalanceString.remove('.');
            qint64 cardBalanceCents = cardBalanceString.toLongLong();

            // Construct window with required parameters
            debitaccountwindow *objDebitAccountWindow = new debitaccountwindow(idAccount, cardBalanceCents);
            objDebitAccountWindow->show();
        }
        else {
            // Data handling to construct creditaccountwindow
            QString idAccount = objCard["idaccount"].toString();

            QString cardBalanceString = objCard["balance"].toString();
            cardBalanceString.remove('.');
            qint64 cardBalanceCents = cardBalanceString.toLongLong();

            QString cardCreditLimitCentsString = objCard["credit_limit"].toString();
            cardCreditLimitCentsString.remove('.');
            qint64 cardCreditLimitCents = cardCreditLimitCentsString.toLongLong();

            // Construct window with required parameters
            creditaccountwindow *objCreditAccountWindow = new creditaccountwindow(idAccount, cardBalanceCents, cardCreditLimitCents);
            objCreditAccountWindow->show();
        }
    } else {
        /*
            Ojelma avaa valintaikkunan, jossa on nappulat Debit ja Credit
            Ohjelma lähettää Array-muodossa taulukon, jossa on kortin molemmat tilit
        */
        cardselectiondialog *objCardSelectionDialog = new cardselectiondialog(cardAccounts);
        objCardSelectionDialog->show();
    }
    reply->deleteLater();
}

