#ifndef LOGINNING_H
#define LOGINNING_H

#include <QDialog>
#include <QMessageBox>

#include "database.h"
#include "maindatabase.h"

namespace Ui {
class loginning;
}

class loginning : public QDialog
{
    Q_OBJECT

signals:
    void showWindow();

public:
    explicit loginning(QWidget *parent = nullptr);
    virtual ~loginning();

private slots:
    void on_exitButton_clicked();

    void on_signInButton_clicked();

    void on_confirmationPsswdLineEdit_editingFinished();

    void on_signUpButton_clicked();

private:
    Ui::loginning *ui;

    MainDataBase *mainDB;
    DataBase *db;
    SearchRecord *search;
};

#endif // LOGINNING_H
