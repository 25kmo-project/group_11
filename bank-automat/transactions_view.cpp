#include "transactions_view.h"
#include "ui_transactions_view.h"

transactions_view::transactions_view(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::transactions_view)
{
    ui->setupUi(this);
}

transactions_view::~transactions_view()
{
    delete ui;
}
