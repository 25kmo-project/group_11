#include "cardwithdrawwindow.h"
#include "ui_cardwithdrawwindow.h"

CardWithdrawWindow::CardWithdrawWindow(Account *newAccount, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CardWithdrawWindow)
    , account(newAccount)
{
    ui->setupUi(this);

    connect(ui->button20, &QPushButton::clicked, this, &CardWithdrawWindow::clickedAmountSlot);
    connect(ui->button40, &QPushButton::clicked, this, &CardWithdrawWindow::clickedAmountSlot);
    connect(ui->button50, &QPushButton::clicked, this, &CardWithdrawWindow::clickedAmountSlot);
    connect(ui->button100, &QPushButton::clicked, this, &CardWithdrawWindow::clickedAmountSlot);
    connect(ui->buttonOther, &QPushButton::clicked, this, &CardWithdrawWindow::clickedOtherAmountSlot);

    connect(ui->buttonConfirm, &QPushButton::clicked, this, &CardWithdrawWindow::confirmOtherWithdrawSlot);

    connect(ui->buttonCancel, &QPushButton::clicked, this, &CardWithdrawWindow::cancelWithdrawSlot);
    connect(ui->buttonCancel_2, &QPushButton::clicked, this, &CardWithdrawWindow::cancelWithdrawSlot);

    double availableBalance = account->getBalance() / 100.00;
    QString balanceText = "Available balance: ";

    QString accountType = account->getAccountType();
    if (accountType == "CREDIT") {
        balanceText = "Available credit: ";
    }

    ui->availableBalance->setText(balanceText + QString::number(availableBalance) + QString("€"));
    ui->availableBalance_2->setText(balanceText + QString::number(availableBalance) + QString("€"));
}

CardWithdrawWindow::~CardWithdrawWindow()
{
    delete ui;
}

void CardWithdrawWindow::clickedAmountSlot() {
    double amount = sender()->property("value").toDouble();

    this->reply = this->account->balanceAction(amount, "withdraw");
    connect(this->reply, &QNetworkReply::finished, this, &CardWithdrawWindow::withdrawDoneSlot);
}

void CardWithdrawWindow::clickedOtherAmountSlot() {
    ui->stackedWidget->setCurrentIndex(1);
}

void CardWithdrawWindow::confirmOtherWithdrawSlot() {
    bool validInput;
    int amount = ui->amountLineEdit->text().toInt(&validInput);

    if (!validInput) {
        ui->errorLabel_2->setText(QString("Please enter a valid number. "));
        return;
    }

    int fiftyEuroBills = std::floor(amount / 50);
    while(fiftyEuroBills >= 0) {
        int remainder = amount - fiftyEuroBills * 50;

        if (remainder % 20 == 0) {
            this->reply = this->account->balanceAction(double(amount), "withdraw");
            connect(this->reply, &QNetworkReply::finished, this, &CardWithdrawWindow::withdrawDoneSlot);
            return;
        }

        fiftyEuroBills--;
    }

    ui->errorLabel_2->setText(QString("Unable to withdraw specified amount with 50€ and 20€ bills. "));
}

void CardWithdrawWindow::cancelWithdrawSlot() {
    this->close();
}

void CardWithdrawWindow::withdrawDoneSlot() {
    QByteArray responseData = this->reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonObject objJson = jsonDoc.object();

    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (statusCode == 403) {
        ui->errorLabel->setText(QString("Unable to withdraw more than available balance, please choose another amount."));
        ui->errorLabel_2->setText(QString("Unable to withdraw more than available balance, please enter a valid amount."));
        return;
    } else if (statusCode != 200) {
        ui->errorLabel->setText(QString("Something went wrong while withdrawing."));
        return;
    }

    this->account->fetchAccountData();

    qDebug() << "Withdraw successful.";
    this->close();
}
