#include "adminmenu.h"

#include "ui_adminmenu.h"

adminmenu::adminmenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::adminmenu)
{
    ui->setupUi(this);
    connect(ui->btnCustomers, &QPushButton::clicked, this, &adminmenu::btnCustomersMenuSlot);
    connect(ui->btnAccounts, &QPushButton::clicked, this, &adminmenu::btnAccountsMenuSlot);
    connect(ui->btnCards, &QPushButton::clicked, this, &adminmenu::btnCardsMenuSlot);
    connect(ui->btnCardAccount, &QPushButton::clicked, this, &adminmenu::btnCardAccountMenuSlot);
}

adminmenu::~adminmenu()
{
    delete ui;
}

void adminmenu::btnCustomersMenuSlot()
{
    customersmenu *objCustomersMenu = new customersmenu(this);
    objCustomersMenu->show();
}

void adminmenu::btnAccountsMenuSlot()
{
    accountsmenu *objAccountsMenu = new accountsmenu(this);
    objAccountsMenu->show();
}

void adminmenu::btnCardsMenuSlot()
{
    cardsmenu *objCardsMenu = new cardsmenu(this);
    objCardsMenu->show();
}

void adminmenu::btnCardAccountMenuSlot()
{
    AccountCardMenu *objAccountCardsMenu = new AccountCardMenu(this);
    objAccountCardsMenu->show();
}

