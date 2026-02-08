#ifndef CARDWITHDRAWWINDOW_H
#define CARDWITHDRAWWINDOW_H

#include <QDialog>
#include <cmath>

#include "../src/account.h"

namespace Ui {
class CardWithdrawWindow;
}

class CardWithdrawWindow : public QDialog
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
};

#endif // CARDWITHDRAWWINDOW_H
