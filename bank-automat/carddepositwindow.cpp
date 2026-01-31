#include "carddepositwindow.h"
#include "ui_carddepositwindow.h"

CardDepositWindow::CardDepositWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CardDepositWindow)
{
    ui->setupUi(this);
}

CardDepositWindow::~CardDepositWindow()
{
    delete ui;
}
