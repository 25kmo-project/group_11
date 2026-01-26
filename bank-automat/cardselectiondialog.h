#ifndef CARDSELECTIONDIALOG_H
#define CARDSELECTIONDIALOG_H

#include <QDialog>

namespace Ui {
class cardselectiondialog;
}

class cardselectiondialog : public QDialog
{
    Q_OBJECT

public:
    explicit cardselectiondialog(QWidget *parent = nullptr);
    ~cardselectiondialog();

    void setToken(const QByteArray &newToken);

private:
    Ui::cardselectiondialog *ui;
    QByteArray token;
};

#endif // CARDSELECTIONDIALOG_H
