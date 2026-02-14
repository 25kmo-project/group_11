#include "transaction_manager.h"
#include "authmanager.h"
#include "../environment.h"

#include <QString>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>

TransactionsManager::TransactionsManager(QObject* parent): QObject(parent) {
    manager = new QNetworkAccessManager(this);
}

void TransactionsManager::onTransactionsReply() {
    auto* reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return;

    reply->deleteLater();

    if (reply->error() != QNetworkReply::NoError) {
        emit fetchFailed(reply->errorString());
        return;
    }

    const QByteArray data = reply->readAll();

    const QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        emit fetchFailed("Invalid JSON format");
        return;
    }

    const QJsonArray array = doc.array();

    m_transactions.clear();
    m_transactions.reserve(array.size());

    for (const QJsonValue& value : array) {
        qDebug() << "Transaction:" << value.toObject();
        m_transactions.append(
            Transaction::fromJson(value.toObject())
            );
    }

    qDebug() << "transaction list lenght: " << m_transactions.length();

    emit transactionsUpdated();
}

void TransactionsManager::fetchTransactions(const QString &accountId, int page, int limit) {
    QUrl url(environment::base_url() + "api/transaction/account/" + accountId);

    QUrlQuery query;
    query.addQueryItem("page", QString::number(page));
    query.addQueryItem("limit", QString::number(limit));
    url.setQuery(query);

    QNetworkRequest request{ url };

    QByteArray token =
        "Bearer " + AuthManager::instance()->getToken().toUtf8();

    request.setRawHeader("Authorization", token);

    QNetworkReply* reply = manager->get(request);

    connect(reply, &QNetworkReply::finished,
            this, &TransactionsManager::onTransactionsReply);
}

void TransactionsManager::createTransaction(const Transaction &t) {
    const QString url =
        environment::base_url() + "api/transaction/";

    QNetworkRequest request{ QUrl(url) };

    const QByteArray token =
        "Bearer " + AuthManager::instance()->getToken().toUtf8();

    request.setRawHeader("Authorization", token);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["idaccount"] = t.account_id;
    json["amount"] = QString::number(t.amount, 'f', 2);
    json["date"] = t.date.toString(Qt::ISODate);
    json["description"] = t.description;

    QJsonDocument doc(json);
    QByteArray body = doc.toJson();

    QNetworkReply* reply = manager->post(request, body);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        reply->deleteLater();

        if (reply->error() != QNetworkReply::NoError) {
            qWarning() << "Failed to create transaction:" << reply->errorString();
            emit transactionCreateFailed(reply->errorString());
            return;
        }

        const QByteArray responseData = reply->readAll();
        QJsonDocument respDoc = QJsonDocument::fromJson(responseData);
        qDebug() << "Transaction created successfully:" << respDoc;

        emit transactionCreated();
    });
}

const QVector<Transaction> TransactionsManager::transactions() const
{
    return m_transactions;
}
