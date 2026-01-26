#include "cardselectiondialog.h"
#include "ui_cardselectiondialog.h"

cardselectiondialog::cardselectiondialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cardselectiondialog)
{
    ui->setupUi(this);
}

cardselectiondialog::~cardselectiondialog()
{
    delete ui;
}

void cardselectiondialog::setToken(const QByteArray &newToken)
{
    token = newToken;
}
