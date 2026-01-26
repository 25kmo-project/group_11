#ifndef CARDSELECTIONDIALOG_H
#define CARDSELECTIONDIALOG_H

#include <QDialog>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "creditaccountwindow.h"
#include "debitaccountwindow.h"

namespace Ui {
class cardselectiondialog;
}

class cardselectiondialog : public QDialog
{
    Q_OBJECT

public:
    explicit cardselectiondialog(
        QJsonArray accounts,
        QWidget *parent = nullptr);
    ~cardselectiondialog();

    void setToken(const QByteArray &newToken);

private:
    Ui::cardselectiondialog *ui;
    QJsonArray accounts;

private slots:
    void btnCreditAccount();
    void btnDebitAccount();
};

#endif // CARDSELECTIONDIALOG_H
