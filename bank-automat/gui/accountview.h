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
    void btnDepositButtonSlot();

public slots:
    void updateBalanceLabel(qint64 newBalance);

};

#endif // ACCOUNTVIEW_H
