#include "customersmenu.h"
#include "ui_customersmenu.h"
#include <QStandardItemModel>

customersmenu::customersmenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::customersmenu)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    connect(ui->btnGetCustomers, &QPushButton::clicked, this, &customersmenu::btnGetCustomers);
    connect(ui->btnAddNewCustomer, &QPushButton::clicked, this, &customersmenu::btnAddNewCustomerMenuSlot);
    connect(ui->btnGetCustomerById, &QPushButton::clicked, this, &customersmenu::btnGetCustomerByIdSlot);
}

customersmenu::~customersmenu()
{
    delete ui;
}

QString customersmenu::getCustomer_base_url() const
{
    return "api/customer";
}

void customersmenu::btnGetCustomers()
{
    // Set url + header
    QString url = environment::base_url() + getCustomer_base_url();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // WEB TOKEN ALKU
    QByteArray myToken = "Bearer " + AuthManager::instance()->getToken().toUtf8();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    // WEB TOKEN LOPPU

    reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &customersmenu::showCustomerSlot);
}

void customersmenu::btnGetCustomerByIdSlot()
{
    // Set url + header
    QString id = ui->textCustomerId->text();
    if (id == "") {
        customersmenu::showInfoslot("Syötä ID");
    } else {
        QString url = environment::base_url() + getCustomer_base_url() + "/" + id;
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        // WEB TOKEN ALKU
        QByteArray myToken = "Bearer " + AuthManager::instance()->getToken().toUtf8();
        request.setRawHeader(QByteArray("Authorization"),(myToken));
        // WEB TOKEN LOPPU

        reply = manager->get(request);
        connect(reply, &QNetworkReply::finished, this, &customersmenu::showCustomerSlot);
    }
}

void customersmenu::showCustomerSlot()
{
    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "Network error:" << reply->errorString();
        reply->deleteLater();
        manager->deleteLater();
        return;
    }

    QByteArray response_data = reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();

    // Clear before made a new array
    customerList.clear();

    // Make a array from customers
    for (const QJsonValue &value : json_array) {
        if (value.isObject()) {
            Customer customer = Customer::mapJson(value.toObject());
            customerList.append(customer);
        }
    }
    customersToTableSlot(customerList);
}

void customersmenu::customersToTableSlot(const QVector<Customer> &customers)
{
    auto *tableModel = new QStandardItemModel(customers.size(), 5, this);
    tableModel -> setHorizontalHeaderLabels({ tr("CustomerID"), tr("First name"), tr("Last name"), tr("Street address"), tr("City") });

    for (int row = 0; row < customers.size(); ++row) {
        const Customer &handlingCustomer = customers[row];
        tableModel->setItem(row, 0, new QStandardItem(QString::number(handlingCustomer.idCustomer)));
        tableModel->setItem(row, 1, new QStandardItem(handlingCustomer.fname));
        tableModel->setItem(row, 2, new QStandardItem(handlingCustomer.lname));
        tableModel->setItem(row, 3, new QStandardItem(handlingCustomer.streetAddress));
        tableModel->setItem(row, 4, new QStandardItem(handlingCustomer.city));
    }
    ui->tableCustomers->setModel(tableModel);
    ui->tableCustomers->verticalHeader()->setVisible(false);
    ui->tableCustomers->resizeColumnsToContents();
    ui->tableCustomers->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    if (customers.size() == 0) {
        customersmenu::showInfoslot("ID doesn't exist");
    }
}

void customersmenu::btnAddNewCustomerMenuSlot()
{
    addcustomermenu *objAddCustomerMenu = new addcustomermenu(this);
    objAddCustomerMenu->show();
}

void customersmenu::showInfoslot(QString info)
{
    ui->labelInfo->setText(info);

    QTimer::singleShot(4000,this,[this]() {
        ui->labelInfo->clear();
    });
}



