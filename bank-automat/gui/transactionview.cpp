#include "transactionview.h"
#include "ui_transactionview.h"

TransactionView::TransactionView(Account *acc, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TransactionView)
{
    ui->setupUi(this);
    manager = new TransactionsManager();
    manager->fetchTransactions(acc->getIdAccount());

    connect(manager, &TransactionsManager::transactionsUpdated, this, [this] {
        refreshTransactionList();
    });

    connect(manager, &TransactionsManager::transactionUpdateFailed, this, [this] {
        refreshTransactionList();
    });
}

TransactionView::~TransactionView()
{
    // Emit a signal so that AccountView can clean up
    emit closeViewSignal();
    delete ui;
}

void TransactionView::refreshTransactionList(){
    const QVector<Transaction>& txs = manager->transactions();
    qDebug() << "recieved list length" << txs.length();

    for (const Transaction& tx : txs) {
        qDebug() << "recieved account ID" <<  tx.account_id;
        qDebug() << "recieved ammount" << tx.amount;
        qDebug() << "recieved date" << tx.date;
        qDebug() << "recieved desc" << tx.description;
        qDebug() << "recieved ID" << tx.id;
    }
}
