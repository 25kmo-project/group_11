#include "carddepositwindow.h"
#include "ui_carddepositwindow.h"

CardDepositWindow::CardDepositWindow(Account &newAccount, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CardDepositWindow)
    , account(newAccount)
{

    ui->setupUi(this);
    connect(ui->btnDeposit, &QPushButton::clicked, this, &CardDepositWindow::btnDepositSlot);
    manager = new QNetworkAccessManager(this);

    //show usable balance and/or credit limit in deposit window
    double balanceEur = account.getBalance()/100.00;
    ui->textBalance->setText(QString::number(balanceEur, 'f',2));
    if(account.getCreditLimit()==0){
        ui->textLimit->clear();
        ui->textLimitDesc->clear();
    }else{
        double limitEur = account.getCreditLimit()/100.00;
        ui->textLimit->setText(QString::number(limitEur, 'f', 2));
    }
}


CardDepositWindow::~CardDepositWindow()
{
    delete ui;
}

void CardDepositWindow::btnDepositSlot()
{
    QString url = environment::base_url()+"api/account/"+account.getIdAccount()+"/deposit";
    QNetworkRequest request(url);
    QByteArray myToken = "Bearer " + AuthManager::instance()->getToken().toUtf8();
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader(QByteArray("Authorization"), (myToken));

    //check customers input
    bool ok;
    double amount = ui->textAmount->text().toDouble(&ok);
    if(!ok){
        ui->labelError->setText("virheellinen syöte");
    }else{
        //Update balance
        QString amountEur = ui->textAmount->text();
        qint64 amountCents = qRound(amount * 100);
        account.setBalance(amountCents + account.getBalance());

        ui->labelError->setText("Add amount & description");
        QJsonObject objDeposit;
        objDeposit.insert("depositAmount", amount);
        objDeposit.insert("description", ui->textDescription->text());

        QJsonDocument jsonDepositDoc(objDeposit);
        reply = manager->sendCustomRequest(request,"PATCH", jsonDepositDoc.toJson());
        connect(reply, &QNetworkReply::finished, this, &CardDepositWindow::depositActionSlot);
    }
}

void CardDepositWindow::depositActionSlot()
{
    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonObject objJson = jsonDoc.object();

    //close window and emit signal to update balance labels on successful deposit
    if(objJson["affectedRows"] == 1){
        this->close();
        emit balanceChanged(account.getBalance());
    }else{
        ui->labelError->setText("Jokin meni vikaan");
    }

    reply->deleteLater();
}
