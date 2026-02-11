#include "adminmenu.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    QString idcard = ui->textCardId->text();
    if (idcard != "admin") {
        MainWindow::showInfoLabelSlot("This user doesn't have rights");
    } else {
        QString url = environment::base_url()+"api/login";
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QJsonObject jObject;

        jObject.insert("idcard", idcard);
        jObject.insert("pin", ui->textPin->text());
        QJsonDocument jsonDoc(jObject);
        reply = manager->post(request, jsonDoc.toJson());
        connect(reply, &QNetworkReply::finished, this, &MainWindow::loginAction);
    }
}

void MainWindow::loginAction()
{
    QByteArray responseData = reply->readAll();
    if (responseData.length()==0) {
        ui->labelInfo->setText("Tarkista backend");
        ui->labelInfo->show();
        qDebug()<<"Tarkista backend";
    } else {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject = jsonDoc.object();
        if(jsonObject.contains("token")) {
            QString token = jsonObject["token"].toString();
            QByteArray tokenBytes = token.toUtf8();
            adminmenu *objAdminMenu = new adminmenu(this);
            AuthManager::instance()->setToken(tokenBytes);
            objAdminMenu->show();
        } else {
            if(jsonObject.value("message").toString()== "Tunnus lukittu"){
                MainWindow::showInfoLabelSlot("Tunnus lukittu");
            } else {
                MainWindow::showInfoLabelSlot("Tarkista ID ja PIN");
            }
            ui->textCardId->clear();
            ui->textPin->clear();
        }
    }
    reply->deleteLater();
}

void MainWindow::showInfoLabelSlot(QString text)
{
    ui->labelInfo->setText(text);
    QTimer::singleShot(4000,this,[this]() {
        ui->labelInfo->clear();
    });
}
