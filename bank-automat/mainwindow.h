#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>
#include "environment.h"
#include "cardselectiondialog.h"
#include "noaccountsview.h"
#include "debitaccountwindow.h"
#include "creditaccountwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QByteArray token;
    QByteArray idcard;

private slots:
    void btnLoginSlot();
    void loginActionSlot();
    void handleAccountsResponse();
};

#endif // MAINWINDOW_H
