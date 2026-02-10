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
#include "src/account.h"

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
    QMap<QString, QString> accounts;
    QTimer *timer;
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    void showError(QString message);

private slots:
    void cardIdEnteredSlot();
    void btnLoginSlot();
    void loginActionSlot();
    void handleAccountsResponse();
    void chooseAccountSlot();
    void logoutSlot();
    void loginTimeoutSlot();
};

#endif // MAINWINDOW_H
