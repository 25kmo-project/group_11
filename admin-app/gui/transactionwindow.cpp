#include "transactionwindow.h"
#include "ui_transactionwindow.h"
#include <QTimer>

transactionwindow::transactionwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::transactionwindow)
{
    ui->setupUi(this);
    connect(ui->btnGetTransactionsById, &QPushButton::clicked, this, &transactionwindow::btnGetTransactionsSlot);
    manager = new QNetworkAccessManager(this);
}

transactionwindow::~transactionwindow()
{
    delete ui;
}

void transactionwindow::btnGetTransactionsSlot()
{
    QString id = ui->textAccountId->text();
    if (id.length() == 0) {
        transactionwindow::showInfoLabelSlot("Give account ID");
    } else {
        QString url = environment::base_url() + "api/transaction/account/all/" + id;
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        // WEB TOKEN ALKU
        QByteArray myToken = "Bearer " + AuthManager::instance()->getToken().toUtf8();
        request.setRawHeader(QByteArray("Authorization"),(myToken));
        // WEB TOKEN LOPPU

        reply = manager->get(request);
        connect(reply, &QNetworkReply::finished, this, &transactionwindow::showTransactionsSlot);
    }
}

void transactionwindow::showTransactionsSlot()
{
    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "Network error:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray response_data = reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();

    transactionList.clear();
    qDebug() << "Testi: " << json_array.size();

    for (const QJsonValue &value : json_array) {
        if (value.isObject()) {
            transaction transaction = transaction::mapJson(value.toObject());
            qDebug() << "Transaction description: " << transaction.amountCents << ". Transaction amount: " << transaction.amountCents;
            transactionList.append(transaction);
        }
    }
    transactionsToTableSlot(transactionList);
}


void transactionwindow::transactionsToTableSlot(const QVector<transaction> &transaction)
{
    auto *tableModel = new QStandardItemModel(transaction.size(), 4, this);
    tableModel -> setHorizontalHeaderLabels({tr("ID"), tr("Amount"), tr("Date"), tr("Description")});

    for (int row = 0; row < transaction.size(); ++row) {
        const class transaction &t = transaction[row];
        tableModel->setItem(row, 0, new QStandardItem(QString::number(t.idTransaction)));
        // Muunnetaan sentit takaisin euroiksi näyttöä varten
        double amountEuro = t.amountCents / 100.0;
        tableModel->setItem(row, 1, new QStandardItem(QString::number(amountEuro, 'f', 2)));
        tableModel->setItem(row, 2, new QStandardItem(t.date.toString("yyyy-MM-dd HH:mm:ss")));
        tableModel->setItem(row, 3, new QStandardItem(t.description));
    }
    ui->tableTransactions->setModel(tableModel);
    ui->tableTransactions->verticalHeader()->setVisible(false);
    ui->tableTransactions->resizeColumnsToContents();

    ui->tableTransactions->setColumnWidth(0, 70);   // ID
    ui->tableTransactions->setColumnWidth(1, 120);   // Amount
    ui->tableTransactions->setColumnWidth(2, 200);  // Date
    ui->tableTransactions->setColumnWidth(3, 150);  // Description

    if (transaction.size() == 0) {
        transactionwindow::showInfoLabelSlot("ID doesn't have transactions or id doesn't exist");
    }
    reply -> deleteLater();
}

void transactionwindow::showInfoLabelSlot(QString text)
{
    ui->labelInfo->setText(text);

    QTimer::singleShot(4000,this,[this]() {
        ui->labelInfo->clear();
    });
}
