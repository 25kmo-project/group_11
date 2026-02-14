#ifndef CARDWITHDRAWWINDOW_H
#define CARDWITHDRAWWINDOW_H

#include <QWidget>
#include <cmath>

#include "../src/account.h"

namespace Ui {
class CardWithdrawWindow;
}

class CardWithdrawWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CardWithdrawWindow(
        Account *newAccount,
        QWidget *parent = nullptr
    );
    ~CardWithdrawWindow();

private:
    Account *account;
    Ui::CardWithdrawWindow *ui;

    QNetworkReply* reply;

private slots:
    void clickedAmountSlot();
    void clickedOtherAmountSlot();
    void confirmOtherWithdrawSlot();
    void cancelWithdrawSlot();
    void withdrawDoneSlot();
    void showInfoLabelSlot1(const QString &text);
    void showInfoLabelSlot2(const QString &text);

signals:
    void infoMessage(const QString &text);
    void closeViewSignal();
};

#endif // CARDWITHDRAWWINDOW_H
