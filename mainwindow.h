#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QSqlQueryModel>

#include "database.h"
#include "loginning.h"
#include "maindatabase.h"
#include "usersediditing.h"
#include "deleteuserfromdb.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

signals:
    void showMainWindow();

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

private slots:
    void on_exitPushButton_clicked();

    void on_addNewUserPushButton_clicked();

    void on_refreshPushButton_clicked();

    void on_deletePushButton_clicked();

private:
    Ui::MainWindow  *ui;

    loginning *loginWindow;
    UsersEdiditing *userEdit;
    deleteUserFromDB *deleteUser;
    DataBase *db;
    QSqlQueryModel *modelMain;

public:
    void refreshWindow();

private:
    void setupMainModel(const QStringList &headers);
    void createUI();
};

#endif // MAINWINDOW_H
