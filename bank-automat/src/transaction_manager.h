#pragma once

#include <QObject>
#include <QVector>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "transaction.h"

class TransactionsManager : public QObject {
    Q_OBJECT

public:
    explicit TransactionsManager(QObject* parent = nullptr);

    void fetchTransactions(const QString& accountId);
    void createTransaction(const Transaction &t);
    void updateTransaction(const Transaction &t);

    const QVector<Transaction>& transactions() const;
signals:
    void transactionsUpdated();
    void fetchFailed(const QString& error);

    void transactionCreated();
    void transactionCreateFailed(const QString& error);

    void transactionUpdated();
    void transactionUpdateFailed(const QString& error);
private slots:
    void onTransactionsReply();
private:
    QNetworkAccessManager *manager;
    QVector<Transaction> m_transactions;
};
