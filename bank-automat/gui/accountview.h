#ifndef ACCOUNTVIEW_H
#define ACCOUNTVIEW_H

#include <QDialog>
#include "../src/account.h"

namespace Ui {
class accountview;
}

class accountview : public QDialog
{
    Q_OBJECT

public:
    explicit accountview(Account *newAccount, QWidget *parent = nullptr);
    ~accountview();

private:
    Ui::accountview *ui;
    Account *account;

private slots:
    void btnTestButtonSlot();
<<<<<<< HEAD
    void btnShowTransactions();
=======
    void btnDepositButtonSlot();

public slots:
    void updateBalanceLabel(qint64 newBalance);

>>>>>>> main
};

#endif // ACCOUNTVIEW_H
