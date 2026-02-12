#ifndef ACCOUNTVIEW_H
#define ACCOUNTVIEW_H

#include <QDialog>
#include "../src/account.h"

namespace Ui {
class AccountView;
}

class AccountView : public QDialog
{
    Q_OBJECT

public:
    explicit AccountView(QString newAccountId, QWidget *parent = nullptr);
    ~AccountView();

private:
    Ui::AccountView *ui;
    Account *account;

private slots:
    void btnTestButtonSlot();
    void btnDepositButtonSlot();
    void btnWithdrawButtonSlot();
    void btnShowTransactionsSlot();
    void btnLogoutSlot();
    void closeViewSlot();

public slots:
    void showInfoLabelSlot(const QString &text);
    void updateBalanceLabel();

signals:
    void userLogoutSignal();

};

#endif // ACCOUNTVIEW_H
