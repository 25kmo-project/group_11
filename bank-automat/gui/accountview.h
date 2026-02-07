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
    explicit AccountView(Account *newAccount, QWidget *parent = nullptr);
    ~AccountView();


private:
    Ui::AccountView *ui;
    Account *account;

private slots:
    void btnTestButtonSlot();
    void btnDepositButtonSlot();
    void btnWithdrawButtonSlot();

public slots:
    void updateBalanceLabel();

};

#endif // ACCOUNTVIEW_H
