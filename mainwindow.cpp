#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = new DataBase();

    if(db->checkingForRecord("admin")){
        QVariantList data;
        data.append("admin");
        data.append("admin");
        db->insertIntoMainTable(data);
        data.clear();
    }

    this->setupMainModel(QStringList() << "ID" << "Логин" << "Пароль");
    this->createUI();

    loginWindow = new loginning();
    connect(loginWindow, &loginning::showWindow, this, &MainWindow::show);

    loginWindow->show();

    userEdit = new UsersEdiditing();
    connect(userEdit, &UsersEdiditing::showWindow, this, &MainWindow::show);

    deleteUser = new deleteUserFromDB();
    connect(deleteUser, &deleteUserFromDB::showWindow, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupMainModel(const QStringList &headers)
{
    modelMain = new QSqlQueryModel(this);
    modelMain->setQuery("SELECT * FROM " TABLE);

    for(int i = 0, j = 0; i < modelMain->columnCount(); i++, j++){
        modelMain->setHeaderData(i, Qt::Horizontal, headers[j]);
    }
}

void MainWindow::createUI()
{
    ui->tableView->setModel(modelMain);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::on_exitPushButton_clicked()
{
    this->close();
}

void MainWindow::on_addNewUserPushButton_clicked()
{
    userEdit->show();
}

void MainWindow::refreshWindow(){
    this->close();
    this->setupMainModel(QStringList() << "ID" << "Логин" << "Пароль");
    this->createUI();
    this->show();
}

void MainWindow::on_refreshPushButton_clicked()
{
    this->refreshWindow();
}

void MainWindow::on_deletePushButton_clicked()
{
    deleteUser->show();
}
