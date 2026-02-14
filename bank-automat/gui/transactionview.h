#ifndef TRANSACTIONVIEW_H
#define TRANSACTIONVIEW_H

#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
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
    void fetchTransactions();
    ~TransactionView();

private slots:
    void on_btn_nextPage_clicked();
    void on_btn_prevPage_clicked();

private:
    Ui::TransactionView *ui;
    Account *account;
    TransactionsManager *manager;
    QVBoxLayout* m_contentLayout;
    int current_page;
};

#endif // TRANSACTIONVIEW_H
