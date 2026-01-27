#ifndef CREDITACCOUNTWINDOW_H
#define CREDITACCOUNTWINDOW_H

#include <QDialog>

namespace Ui {
class creditaccountwindow;
}

class creditaccountwindow : public QDialog
{
    Q_OBJECT

public:
    explicit creditaccountwindow(
        const QString &idaccount,
        qint64 balanceCents,
        qint64 creditLimitCents,
        QWidget *parent = nullptr);
    ~creditaccountwindow();

    void setIdaccount(const QString &newIdaccount);
    void setBalanceCents(qint64 newBalanceCents);
    void setCredlitLimitCents(qint64 newCredlitLimitCents);

private:
    Ui::creditaccountwindow *ui;
};

#endif // CREDITACCOUNTWINDOW_H
