#ifndef CARDWITHDRAWWINDOW_H
#define CARDWITHDRAWWINDOW_H

#include <QDialog>

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

private slots:
    void clickedAmountSlot();
    void clickedOtherAmountSlot();
    void confirmOtherWithdrawSlot();
    void cancelWithdrawSlot();
};

#endif // CARDWITHDRAWWINDOW_H
