#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "environment.h"
#include "src/authmanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qApp->installEventFilter(this);
    connect(ui->btnNext, &QPushButton::clicked, this, &MainWindow::cardIdEnteredSlot);
    connect(ui->btnLogin, &QPushButton::clicked, this, &MainWindow::btnLoginSlot);
    connect(ui->btnDebit, &QPushButton::clicked, this, &MainWindow::chooseAccountSlot);
    connect(ui->btnCredit, &QPushButton::clicked, this, &MainWindow::chooseAccountSlot);
    connect(ui->btnLogout, &QPushButton::clicked, this, &MainWindow::logoutSlot);
    manager = new QNetworkAccessManager(this);

    // Inactivity timer 30 seconds
    this->inactivityTimer = new QTimer(this);
    this->inactivityTimer->setSingleShot(true);
    connect(inactivityTimer, &QTimer::timeout, this, &MainWindow::inactivityTimeoutSlot);
    this->inactivityTimer->start(30000);

    // Create timer and connect it to a slot that clears lineedits after 10 seconds of inactivity
    this->timer = new QTimer(this);
    this->timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, this, &MainWindow::loginTimeoutSlot);

    // Timer resets back to ten seconds every time card ID is edited
    // This means if the user stops typing for 10 seconds, the card ID and PIN fields are cleared
    connect(ui->textCardId, &QLineEdit::textEdited, this, [this]() {
        this->timer->start(10000); // 10 seconds
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cardIdEnteredSlot() {
    // Check that the card ID field is not empty
    if (ui->textCardId->text() == "") {
        showError("Card ID cannot be empty.");
        return;
    }

    // After card ID is entered, move to card PIN page and start timer for 10 seconds
    // user has 10 seconds to enter PIN, otherwise ID and PIN are cleared and app goes back to card ID screen
    ui->stackedWidget->setCurrentIndex(1);
    this->timer->start(10000);
}

void MainWindow::btnLoginSlot() {
    // Check that the PIN code field is not empty
    if (ui->textPin->text() == "") {
        showError("Card ID or PIN code cannot be empty.");
        return;
    }

    // Stopping timer here incase the API request takes time to process
    this->timer->stop();

    // Set request url and header
    QString url = environment::base_url() + "api/login/";
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Create object, where to insert idcard and pin
    QJsonObject loginObject;
    loginObject.insert("idcard", ui->textCardId->text());
    loginObject.insert("pin", ui->textPin->text());

    // Clear line edits
    ui->textCardId->clear();
    ui->textPin->clear();

    // Create QJsonDocument and post request
    QJsonDocument jsonLoginDoc(loginObject);
    reply = manager->post(request, jsonLoginDoc.toJson());
    connect(reply, &QNetworkReply::finished, this, &MainWindow::loginActionSlot);
}

void MainWindow::loginActionSlot() {
    // Show error based on which status code was received from the API and return back to
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << statusCode;
    if (statusCode != 200) {
        ui->stackedWidget->setCurrentIndex(0);

        switch (statusCode) {
        case 0:
            showError("Connection error, try again later.");
            return;
            break;
        case 403:
            showError("Too many failed login attemps, card has been locked.");
            return;
            break;
        case 404:
            showError("ID and PIN do not match any cards.");
            return;
            break;
        case 500:
            showError("A server error has occurred, try again later.");
            return;
            break;
        }
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObject = jsonDoc.object();

    // If responseData have token -> Login is successful
    if (jsonObject.contains("token")) {
        // Type conversion
        QString token = jsonObject["token"].toString();
        QByteArray tokenBytes = token.toUtf8();
        QByteArray idcard = jsonObject["idcard"].toString().toUtf8();

        // Set token to AuthManager to usable easier elsewhere
        AuthManager::instance()->setToken(tokenBytes);

        // URL to get card accounts
        QString url = environment::base_url() + "api/card/" + idcard + "/accounts/";
        QNetworkRequest request(url);

        //WEB TOKEN START
        QByteArray myToken = "Bearer " + AuthManager::instance()->getToken().toUtf8();
        request.setRawHeader(QByteArray("Authorization"),(myToken));
        //WEB TOKEN END

        reply = manager->get(request);
        connect(reply, &QNetworkReply::finished, this, &MainWindow::handleAccountsResponse);
    } else {
        showError("Something went wrong.");
    }
}

void MainWindow::handleAccountsResponse() {
    QByteArray responseData = reply->readAll();
    QJsonDocument jsonCardDoc = QJsonDocument::fromJson(responseData);
    QJsonArray cardAccounts = jsonCardDoc.array();
    // If no accounts found, show noAccountView and start timer for 10 seconds to log out automatically
    if (cardAccounts.size() == 0) {
        this->timer->start(10000);
        ui->stackedWidget->setCurrentIndex(2);
        ui->frameAccounts->hide();
        ui->lblNoAccounts->show();
        return;
    }

    for (const auto &account : cardAccounts) {
        QJsonObject obj = account.toObject();

        // Insert values into QMap (resembles JSON), where the key is the account type and the value for the key is the account's ID
        this->accounts.insert(obj["account_type"].toString(), obj["idaccount"].toString());
    }

    if (cardAccounts.size() == 1) {
        // Get first value from accounts and create AccountView with it
        QString key = this->accounts.firstKey();
        objAccountView = new AccountView(this->accounts.value(key), this);
        ui->stackedWidget->addWidget(objAccountView);
        ui->stackedWidget->setCurrentWidget(objAccountView);
        connect(objAccountView, &AccountView::userLogoutSignal, this, &MainWindow::logoutSlot);

        this->accounts.clear();
    } else if (cardAccounts.size() == 2) {
        // If card has two accounts, change to card selection page (index 1)
        // User has 10 seconds to choose an account, otherwise they are automatically logged out
        this->timer->start(10000);
        ui->stackedWidget->setCurrentIndex(2);
        ui->lblNoAccounts->hide();
        ui->frameAccounts->show();
    }
    reply->deleteLater();
}

void MainWindow::chooseAccountSlot() {
    QString buttonAccountType = sender()->property("accountType").toString();

    objAccountView = new AccountView(this->accounts.value(buttonAccountType), this);

    ui->stackedWidget->addWidget(objAccountView);
    ui->stackedWidget->setCurrentWidget(objAccountView);

    connect(objAccountView, &AccountView::userLogoutSignal, this, &MainWindow::logoutSlot);

    // After AccountView has been created with selected account, clear QMap and return MainWindow back to login screen
    this->accounts.clear();
    //ui->stackedWidget->setCurrentIndex(0);
    this->timer->stop();
}

void MainWindow::logoutSlot() {
    AuthManager::instance()->clearToken();
    this->accounts.clear();
    ui->stackedWidget->setCurrentIndex(0);

    if (objAccountView != nullptr) {
        ui->stackedWidget->removeWidget(objAccountView);
        objAccountView->deleteLater();
        objAccountView = nullptr;
    }
}

void MainWindow::loginTimeoutSlot() {
    if (ui->stackedWidget->currentIndex() == 0) {
        showError("Cleared fields due to inactivity.");
    } else if (ui->stackedWidget->currentIndex() == 1) {
        showError("PIN code was not entered in 10 seconds.");
    } else {
        AuthManager::instance()->clearToken();
        showError("Automatically logged out due to inactivity.");
    }

    ui->textCardId->clear();
    ui->textPin->clear();
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::inactivityTimeoutSlot()
{
    AuthManager::instance()->clearToken();

    ui->textCardId->clear();
    ui->textPin->clear();
    ui->stackedWidget->setCurrentIndex(0);

    ui->stackedWidget->removeWidget(objAccountView);
    objAccountView->deleteLater();
    objAccountView=nullptr;

    showError("Automatically logged out due to inactivity.");
}

void MainWindow::showError(QString message) {
    // Lazy solution, can be changed for a better solution
    // Both pages need to have their own error label so we change both of them at the same time
    ui->labelError->setText(message);
    //ui->labelError->show();

    ui->labelError_2->setText(message);
    //ui->labelError_2->show();

    //Timer for labelError
    QTimer::singleShot(4000, this, [this]() {
        ui->labelError->clear();
        ui->labelError_2->clear();
    });
}


bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type()==QEvent::MouseButtonPress||
        event->type() == QEvent::MouseMove ||
        event->type() == QEvent::KeyPress ||
        event->type() == QEvent::Wheel){
        inactivityTimer->start();
    }
    return QMainWindow::eventFilter(obj, event);
}

