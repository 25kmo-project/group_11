#include "transactionview.h"
#include "ui_transactionview.h"

TransactionView::TransactionView(Account *acc, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TransactionView)
{
    account = acc;
    current_page = 1;
    ui->setupUi(this);
    manager = new TransactionsManager();
    manager->fetchTransactions(acc->getIdAccount());

    connect(manager, &TransactionsManager::transactionsUpdated, this, [this] {
        refreshTransactionList();
    });

    connect(manager, &TransactionsManager::transactionUpdateFailed, this, [this] {
        //refreshTransactionList();
    });
}

class TransactionWidget : public QWidget {
public:
    explicit TransactionWidget(const Transaction& tx, QWidget* parent = nullptr)
        : QWidget(parent)
    {
        auto* layout = new QVBoxLayout(this);

        auto* amountLabel = new QLabel(
            QString("%1 €").arg(tx.amount, 0, 'f', 2), this);

        if (tx.amount >= 0) {
            amountLabel->setStyleSheet("color: #2ecc71;");
        } else {
            amountLabel->setStyleSheet("color: #e74c3c;");
        }

        auto* descLabel = new QLabel(tx.description, this);

        QFont amountFont;
        amountFont.setPointSize(14);
        amountFont.setBold(true);

        QFont descFont;
        descFont.setPointSize(10);

        setObjectName("transactionCard");
        setAttribute(Qt::WA_StyledBackground, true);

        QString accent = tx.amount >= 0 ? "#27ae60" : "#c0392b";

        setStyleSheet(QString(R"(
            QWidget#transactionCard {
                background-color: #BFFFDD;
                border-left: 4px solid %1;
                border-radius: 8px;
            }

        )").arg(accent));

        amountLabel->setFont(amountFont);
        descLabel->setFont(descFont);

        layout->addWidget(amountLabel);
        layout->addWidget(descLabel);
    }
};

void TransactionView::refreshTransactionList(){
    const QVector<Transaction>& txs = manager->transactions();
    qDebug() << "recieved list length" << txs.length();

    if (txs.empty()){
        current_page -= 1;
        return;
    }

    QWidget* contentWidget = new QWidget(this);
    QVBoxLayout* contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setAlignment(Qt::AlignTop); // important for scroll areas
    contentLayout->setSpacing(8);
    contentWidget->setStyleSheet("background-color: transparent;");

    ui->scrollArea->setWidget(contentWidget);
    ui->scrollArea->setWidgetResizable(true);

    m_contentLayout = contentLayout;
    QLayoutItem* item;
    while ((item = m_contentLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    for (const auto& tx : txs) {
        auto* widget = new TransactionWidget(tx);
        m_contentLayout->addWidget(widget);
    }

    ui->label_page->setText(QString("Page: %1").arg(current_page));

    for (const Transaction& tx : txs) {
        qDebug() << "recieved account ID" <<  tx.account_id;
        qDebug() << "recieved ammount" << tx.amount;
        qDebug() << "recieved date" << tx.date;
        qDebug() << "recieved desc" << tx.description;
        qDebug() << "recieved ID" << tx.id;
    }
}

TransactionView::~TransactionView()
{
    delete ui;
}

void TransactionView::on_btn_nextPage_clicked()
{
    current_page += 1;
    manager->fetchTransactions(account->getIdAccount(), current_page);
}

void TransactionView::on_btn_prevPage_clicked()
{
    if (current_page > 1) {
        current_page -= 1;
        manager->fetchTransactions(account->getIdAccount(), current_page);
    }
}
