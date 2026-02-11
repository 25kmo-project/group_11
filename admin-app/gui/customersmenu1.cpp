#include "customersmenu1.h"
#include "ui_customers.h"

customersmenu::customersmenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::customersmenu)
{
    ui->setupUi(this);
    connect(ui->btnGetCustomers, &QPushButton::clicked, this, &customers::btnGetCustomers);
}

customersmenu::~customersmenu()
{
    delete ui;
}

void customers::btnGetCustomers()
{
    qDebug()<<"testi";
}
