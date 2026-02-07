#ifndef TRANSACTIONVIEW_H
#define TRANSACTIONVIEW_H

#include <QDialog>
#include "../src/account.h"
#include "../src/transaction_manager.h"

namespace Ui {
class TransactionView;
}

class TransactionView : public QDialog
{
    Q_OBJECT

public:
    explicit TransactionView(Account *acc, QWidget *parent = nullptr);
    void refreshTransactionList();
    ~TransactionView();

private:
    Ui::TransactionView *ui;
    Account *acc;
    TransactionsManager *manager;
};

#endif // TRANSACTIONVIEW_H
