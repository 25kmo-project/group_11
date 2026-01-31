#ifndef CARDDEPOSITWINDOW_H
#define CARDDEPOSITWINDOW_H

#include <QDialog>

namespace Ui {
class CardDepositWindow;
}

class CardDepositWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CardDepositWindow(QWidget *parent = nullptr);
    ~CardDepositWindow();

private:
    Ui::CardDepositWindow *ui;
};

#endif // CARDDEPOSITWINDOW_H
