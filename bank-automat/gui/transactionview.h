#ifndef TRANSACTIONVIEW_H
#define TRANSACTIONVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QWidget>
#include "../src/account.h"
#include "../src/transaction_manager.h"

namespace Ui {
class TransactionView;
}

class TransactionView : public QWidget
{
    Q_OBJECT

public:
    explicit TransactionView(Account *acc, QWidget *parent = nullptr);
    ~TransactionView();

private slots:
    void on_btn_nextPage_clicked();
    void on_btn_prevPage_clicked();

    void on_btn_back_clicked();

private:
    void refreshTransactionList();
    void fetchTransactions();
    void TransactionErrorView(QString error_msg);
    Ui::TransactionView *ui;
    Account *account;
    TransactionsManager *manager;
    QVBoxLayout* m_contentLayout;
    int current_page;

signals:
    void closeViewSignal();
};

#endif // TRANSACTIONVIEW_H
