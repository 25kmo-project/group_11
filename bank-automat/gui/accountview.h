#ifndef ACCOUNTVIEW_H
#define ACCOUNTVIEW_H

#include <QWidget>
#include "../src/account.h"
#include "../src/customer.h"

namespace Ui {
class AccountView;
}

class AccountView : public QWidget
{
    Q_OBJECT

public:
    explicit AccountView(QString newAccountId, QWidget *parent = nullptr);
    ~AccountView();

private:
    Ui::AccountView *ui;
    Account *account;
    Customer *customer;

private slots:
    void btnTestButtonSlot();
    void initializeViewSlot();
    void updateCustomerLabel();
    void btnDepositButtonSlot();
    void btnWithdrawButtonSlot();
    void btnShowTransactionsSlot();
    void btnLogoutSlot();
    void closeViewSlot();

public slots:
    void getCustomerDataSlot();
    void showInfoLabelSlot(const QString &text);
    void updateBalanceLabel();

signals:
    void userLogoutSignal();

};

#endif // ACCOUNTVIEW_H
