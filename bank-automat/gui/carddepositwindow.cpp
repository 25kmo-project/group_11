#include "accountview.h"
#include "carddepositwindow.h"
#include "ui_carddepositwindow.h"

CardDepositWindow::CardDepositWindow(Account *newAccount, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CardDepositWindow)
    , account(newAccount)
{

    ui->setupUi(this);
    connect(ui->btnDeposit, &QPushButton::clicked, this, &CardDepositWindow::btnDepositSlot);
    connect(ui->btnCancelDeposit, &QPushButton::clicked, this, &CardDepositWindow::cancelDepositSlot);
    manager = new QNetworkAccessManager(this);

    QString accountType = account->getAccountType();
    if (accountType == "CREDIT") {
        ui->label_2->setText(QString("Available credit: "));

        double limitEur = account->getCreditLimit()/100.00;
        ui->textLimit->setText(QString::number(limitEur, 'f', 2) + QString("€"));
    } else {
        ui->textLimit->clear();
        ui->textLimitDesc->clear();
    }

    //show usable balance and/or credit limit in deposit window
    double balanceEur = account->getBalance()/100.00;
    ui->textBalance->setText(QString::number(balanceEur, 'f',2) + QString("€"));
}


CardDepositWindow::~CardDepositWindow()
{
    // Emit a signal so that AccountView can clean up
    emit closeViewSignal();
    delete ui;
}

void CardDepositWindow::btnDepositSlot()
{
    //check customers input
    bool ok;
    double amount = ui->textAmount->text().toDouble(&ok);
    if(!ok){
        CardDepositWindow::showLabelErrorSlot("Invalid input");
    }else{
        this->reply = this->account->balanceAction(amount, "deposit");
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
        this->account->fetchAccountData();
        emit infoMessage("Deposit successful!");
        this->deleteLater();
    }else{
        CardDepositWindow::showLabelErrorSlot("Something went wrong");
    }
    reply->deleteLater();
}

void CardDepositWindow::showLabelErrorSlot(QString text)
{
    ui->labelInfo->setText(text);
    QTimer::singleShot(4000,this,[this]() {
        ui->labelInfo->clear();
    });
}

void CardDepositWindow::cancelDepositSlot()
{
    emit infoMessage("Deposit canceled");
    this->deleteLater();
}
