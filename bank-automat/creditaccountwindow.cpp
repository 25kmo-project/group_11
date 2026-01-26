#include "creditaccountwindow.h"
#include "ui_creditaccountwindow.h"

creditaccountwindow::creditaccountwindow(const QString &idaccount, qint64 balanceCents, qint64 creditLimitCents, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::creditaccountwindow)
{
    ui->setupUi(this);

    // Konsoliin teksti mitä muuttujia olio saa konstruktorin yhteydessä
    qDebug().noquote() << "[CreditAccountWindow created]";
    qDebug().noquote() << "idaccount:" << idaccount;
    qDebug().noquote() << "balanceCents:" << balanceCents << "cents";
    qDebug().noquote() << "creditLimitCents:" << creditLimitCents << "cents";

}


creditaccountwindow::~creditaccountwindow()
{
    delete ui;
}

