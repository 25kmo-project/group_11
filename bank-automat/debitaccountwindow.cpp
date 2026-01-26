#include "debitaccountwindow.h"
#include "ui_debitaccountwindow.h"

debitaccountwindow::debitaccountwindow(const QString &idaccount, qint64 balanceCents, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::debitaccountwindow)
{
    ui->setupUi(this);

    // Konsoliin teksti mitä muuttujia olio saa konstruktorin yhteydessä
    qDebug().noquote() << "[DebitAccountWindow created]";
    qDebug().noquote() << "idaccount:" << idaccount;
    qDebug().noquote() << "balanceCents:" << balanceCents << "cents";
}

debitaccountwindow::~debitaccountwindow()
{
    delete ui;
}
