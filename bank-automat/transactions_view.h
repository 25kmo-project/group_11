#ifndef TRANSACTIONS_VIEW_H
#define TRANSACTIONS_VIEW_H

#include <QDialog>

namespace Ui {
class transactions_view;
}

class transactions_view : public QDialog
{
    Q_OBJECT

public:
    explicit transactions_view(QWidget *parent = nullptr);
    ~transactions_view();

private:
    Ui::transactions_view *ui;
};

#endif // TRANSACTIONS_VIEW_H
