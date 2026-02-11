#include "accountsmenu.h"
#include "ui_accountsmenu.h"

accountsmenu::accountsmenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::accountsmenu)
{
    ui->setupUi(this);
    connect(ui->btnGetAccounts, &QPushButton::clicked, this, &accountsmenu::btnGetAccountsSlot);
    connect(ui->btnCreateDeleteAccount, &QPushButton::clicked, this, &accountsmenu::btnAddDeleteSlot);
    connect(ui->btnGetAccountById, &QPushButton::clicked, this, &accountsmenu::btnGetAccountByIdSlot);
    manager = new QNetworkAccessManager(this);
}

QString accountsmenu::getAccountAdd_base_url() const
{
    return "api/account";
}

accountsmenu::~accountsmenu()
{
    delete ui;
}

void accountsmenu::btnGetAccountsSlot()
{
    QString url = environment::base_url() + accountsmenu::getAccountAdd_base_url();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // WEB TOKEN ALKU
    QByteArray myToken = "Bearer " + AuthManager::instance()->getToken().toUtf8();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    // WEB TOKEN LOPPU

    reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &accountsmenu::showAccountsSlot);
}

void accountsmenu::btnGetAccountByIdSlot()
{
    QString id = ui->textAccountId->text();
    if (id == "") {
        accountsmenu::showInfoslot("Syötä ID");
    } else {
        // Set url + header
        QString url = environment::base_url() + accountsmenu::getAccountAdd_base_url() + "/" + id;
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        // WEB TOKEN ALKU
        QByteArray myToken = "Bearer " + AuthManager::instance()->getToken().toUtf8();
        request.setRawHeader(QByteArray("Authorization"),(myToken));
        // WEB TOKEN LOPPU

        reply = manager->get(request);
        connect(reply, &QNetworkReply::finished, this, &accountsmenu::showAccountsSlot);
    }
}

void accountsmenu::btnAddDeleteSlot()
{
    addaccountmenu *objAddAccountMenu = new addaccountmenu(this);
    objAddAccountMenu->show();
}

void accountsmenu::showAccountsSlot()
{
    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "Network error:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray response_data = reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();

    accountList.clear();

    for (const QJsonValue &value : json_array) {
        if (value.isObject()) {
            Account account = Account::mapJson(value.toObject());
            // qDebug() << "Account type: " << account.accountType << " Balance: " << account.balance;
            accountList.append(account);
        }
    }
    accountsToTableSlot(accountList);
}

void accountsmenu::accountsToTableSlot(const QVector<Account> &account)
{
    auto *tableModel = new QStandardItemModel(account.size(), 5, this);
    tableModel -> setHorizontalHeaderLabels({tr("AccountID"), tr("AccountType"), tr("Balance"), tr("CreditLimit"), tr("OwnerID")});

    for (int row = 0; row < account.size(); row++) {
        const Account &handlingAccount = account[row];
        tableModel->setItem(row, 0, new QStandardItem(QString::number(handlingAccount.idAccount)));
        tableModel->setItem(row, 1, new QStandardItem(handlingAccount.accountType));
        tableModel->setItem(row, 2, new QStandardItem(QString::number(handlingAccount.balance)));
        tableModel->setItem(row, 3, new QStandardItem(QString::number(handlingAccount.creditLimit)));
        tableModel->setItem(row, 4, new QStandardItem(QString::number(handlingAccount.idOwner)));
    }
    ui->tableAccounts->setModel(tableModel);
    ui->tableAccounts->verticalHeader()->setVisible(false);
    ui->tableAccounts->resizeColumnsToContents();
    ui->tableAccounts->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    if (account.size() == 0) {
        accountsmenu::showInfoslot("ID:llä ei tiliä");
    }
    reply -> deleteLater();
}

void accountsmenu::showInfoslot(QString info)
{
    ui->labelInfo->setText(info);

    QTimer::singleShot(4000,this,[this]() {
        ui->labelInfo->clear();
    });
}
