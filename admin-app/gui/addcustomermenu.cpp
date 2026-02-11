#include "addcustomermenu.h"
#include "ui_addcustomermenu.h"

addcustomermenu::addcustomermenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addcustomermenu)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    connect(ui->btnSendCustomerData, &QPushButton::clicked, this, &addcustomermenu::btnGetCustomerData);
    connect(ui->btnSendDeleteCustomer, &QPushButton::clicked, this, &addcustomermenu::btnDeleteCustomerSlot);
}

addcustomermenu::~addcustomermenu()
{
    delete ui;
}

QString addcustomermenu::getCustomerAdd_base_url() const
{
    return "api/customer";
}

void addcustomermenu::btnGetCustomerData()
{
    // Base url + header
    QString url = environment::base_url() + addcustomermenu::getCustomerAdd_base_url();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Read needed parameters to object which to post
    QString fname = ui->textFirstName->text();
    QString lname = ui->textLastName->text();

    if (fname.isEmpty() || lname.isEmpty()) {
        addcustomermenu::showInfoLabelSlot("Give first- and lastname");
    } else {
        QJsonObject customerObject;
        customerObject.insert("fname", fname);
        customerObject.insert("lname", lname);
        customerObject.insert("street_address", ui->textStreetAddress->text());
        customerObject.insert("city", ui->textCity->text());

        //WEBTOKEN ALKU
        QByteArray myToken="Bearer "+ AuthManager::instance()->getToken().toUtf8();
        request.setRawHeader(QByteArray("Authorization"),(myToken));
        //WEBTOKEN LOPPU

        QJsonDocument customerJsonDoc(customerObject);
        reply = manager->post(request, customerJsonDoc.toJson());
        connect(reply, &QNetworkReply::finished, this, &addcustomermenu::addCustomerSlot);
    }
}

void addcustomermenu::addCustomerSlot()
{
    response_data = reply->readAll();
    qDebug() << response_data;
    if (response_data.contains("insertId")) {
        addcustomermenu::showInfoLabelSlot("Customer added");
    } else {
        addcustomermenu::showInfoLabelSlot("Customer add failed");
    }
    reply->deleteLater();
}

void addcustomermenu::btnDeleteCustomerSlot()
{
    QString id = ui->textCustomerId->text();
    QString url = environment::base_url() + addcustomermenu::getCustomerAdd_base_url() + "/" + id;
    QNetworkRequest request(url);

    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+ AuthManager::instance()->getToken().toUtf8();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    reply = manager->deleteResource(request);
    connect(reply, &QNetworkReply::finished, this, &addcustomermenu::deleteCustomerSlot);
}


void addcustomermenu::deleteCustomerSlot()
{
    response_data = reply->readAll();
    qDebug() << response_data;
    if (response_data.contains("affectedRows")) {
        addcustomermenu::showInfoLabelSlot("Customer deleted");
    } else {
        addcustomermenu::showInfoLabelSlot("Delete failed");
    }
    reply -> deleteLater();
}

void addcustomermenu::showInfoLabelSlot(QString text)
{
    ui->labelInfo->setText(text);
    QTimer::singleShot(4000,this,[this]() {
        ui->labelInfo->clear();
    });
}

