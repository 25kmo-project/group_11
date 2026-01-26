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
    QJsonDocument jsonLoginDoc(loginObject);
    reply= manager->post(request, jsonLoginDoc.toJson());
    connect(reply, &QNetworkReply::finished, this, &MainWindow::loginActionSlot);
}

void MainWindow::loginActionSlot()
{
    QByteArray responseData = reply->readAll();

    // Check are backendu up
    if (responseData.length()==0) {
        qDebug()<< "Tarkista backend";
        ui->labelInfo->setText("Yhteysvirhe");
        ui->labelInfo->show();

        //Timer for labelInfo
        QTimer::singleShot(5000, this, [this]() {
            ui->labelInfo->clear();
        });
    }

    // If cardID or PIN is empty
    if (responseData.length()==1) {
        qDebug() << "testi1";
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject = jsonDoc.object();
        ui->labelInfo->setText(jsonObject.value("message").toString());
        ui->labelInfo->show();

        //Timer for labelInfo
        QTimer::singleShot(5000, this, [this]() {
            ui->labelInfo->clear();
        });

    // If backend is up, then check CardID & PIN
    } else {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject = jsonDoc.object();
        for (auto it = jsonObject.begin(); it != jsonObject.end(); ++it) {
            qDebug() << it.key() << ":" << it.value();
        }
        // If card locked
        if(jsonObject.value("message").toString()== "Tunnus lukittu") {
            ui->labelInfo->setText("Tunnus lukittu");
            ui->labelInfo->show();

            //Timer for labelInfo
            QTimer::singleShot(3000, this, [this]() {
                ui->labelInfo->clear();
            });

            // Clear line edits
            ui->textCardId->clear();
            ui->textPin->clear();
        }
        // If PIN or Idcard doesnt have input
        if(jsonObject.value("message").toString()== "Idcard tai PIN puuttuu.") {
            ui->labelInfo->setText("Idcard tai PIN puuttuu.");
            ui->labelInfo->show();

            //Timer for labelInfo
            QTimer::singleShot(3000, this, [this]() {
                ui->labelInfo->clear();
            });

            // Clear line edits
            ui->textCardId->clear();
            ui->textPin->clear();
        }

        if (jsonObject.contains("token")) {
            QString token = jsonObject["token"].toString();
            QByteArray tokenBytes = token.toUtf8();
            cardselectiondialog *objCardSelectionDialog = new cardselectiondialog(this);
            objCardSelectionDialog->setToken(tokenBytes);
            objCardSelectionDialog->show();
        }
    }
    reply->deleteLater();
}

