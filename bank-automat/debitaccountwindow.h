#ifndef DEBITACCOUNTWINDOW_H
#define DEBITACCOUNTWINDOW_H

#include <QDialog>

namespace Ui {
class debitaccountwindow;
}

class debitaccountwindow : public QDialog
{
    Q_OBJECT

public:
    explicit debitaccountwindow(
        const QString &idaccount,
        qint64 balanceCents,
        QWidget *parent = nullptr);
    ~debitaccountwindow();

    void setBalanceCents(qint64 newBalanceCents);

    void setIdaccount(const QString &newIdaccount);

private:
    Ui::debitaccountwindow *ui;
};

#endif // DEBITACCOUNTWINDOW_H
