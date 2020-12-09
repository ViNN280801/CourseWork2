#ifndef USERSEDIDITING_H
#define USERSEDIDITING_H

#include <QWidget>
#include <QMessageBox>
#include <cstring>

#include "database.h"

namespace Ui {
class UsersEdiditing;
}

class UsersEdiditing : public QWidget
{
    Q_OBJECT

signals:
    void showWindow();

public:
    explicit UsersEdiditing(QWidget *parent = nullptr);
    ~UsersEdiditing();

private slots:
    void on_addNewUserPushButton_clicked();

private:
    Ui::UsersEdiditing *ui;

    DataBase *db;
};

#endif // USERSEDIDITING_H
