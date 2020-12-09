#ifndef DELETEUSERFROMDB_H
#define DELETEUSERFROMDB_H

#include <QWidget>
#include <QSqlQuery>
#include <QMessageBox>

#include "database.h"

namespace Ui {
class deleteUserFromDB;
}

class deleteUserFromDB : public QWidget
{
    Q_OBJECT

signals:
    void showWindow();

public:
    explicit deleteUserFromDB(QWidget *parent = nullptr);
    ~deleteUserFromDB();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_loginCheckBox_stateChanged(int arg1);

private:
    Ui::deleteUserFromDB *ui;

    DataBase *db;
};

#endif // DELETEUSERFROMDB_H
