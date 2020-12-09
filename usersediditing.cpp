#include "usersediditing.h"
#include "ui_usersediditing.h"

UsersEdiditing::UsersEdiditing(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UsersEdiditing)
{
    ui->setupUi(this);

    db = new DataBase();
}

UsersEdiditing::~UsersEdiditing()
{
    delete ui;
}

void UsersEdiditing::on_addNewUserPushButton_clicked()
{
    if(db->checkingForIDInWeatherDB(ui->whichLine->text().toInt())){
        if(ui->loginLineEdit->text() != nullptr && ui->psswdLineEdit->text() != nullptr &&
                ui->whichLine->text() != nullptr){
            if(ui->loginLineEdit->text() != "admin"){
                if(db->checkingForRecord(ui->loginLineEdit->text())){
                    QString login = ui->loginLineEdit->text();
                    QString psswd = ui->psswdLineEdit->text();
                    int id = ui->whichLine->text().toInt();

                    QVariantList data;

                    data.append(login);
                    data.append(psswd);

                    if(db->checkingForID(id)){
                        db->insertIntoMainTableWithKnownID(data, id);

                        QMessageBox _msgBox;
                        _msgBox.setWindowTitle("Добавление");
                        _msgBox.setText("Пользователь успешно добавлен.");
                        _msgBox.exec();
                    }
                    else if(!db->checkingForID(id)){
                        QMessageBox msgBox;
                        msgBox.setWindowTitle("Внимание");
                        msgBox.setText("Поле с таким ID уже занято.");
                        msgBox.exec();
                    }
                    else{
                        QMessageBox msgBox;
                        msgBox.setWindowTitle("Внимание");
                        msgBox.setText("Произошла неизвестная ошибка!");
                        msgBox.exec();
                    }

                    data.clear();

                    ui->loginLineEdit->clear();
                    ui->psswdLineEdit->clear();
                    ui->whichLine->clear();

                    this->close();
                }
                else if(!db->checkingForRecord(ui->loginLineEdit->text())){
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Warning");
                    msgBox.setText("Can't add new user with this login.");
                    msgBox.exec();

                    ui->loginLineEdit->clear();
                    ui->psswdLineEdit->clear();
                    ui->whichLine->clear();
                }
                else{
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Внимание");
                    msgBox.setText("Произошла неизвестная ошибка!");
                    msgBox.exec();

                    ui->loginLineEdit->clear();
                    ui->psswdLineEdit->clear();
                    ui->whichLine->clear();
                }
            }
            else if(ui->loginLineEdit->text() == "admin"){
                QMessageBox msgBox;
                msgBox.setWindowTitle("Внимание");
                msgBox.setText("Невозможно добавиь пользователя с логином \"admin\"");
                msgBox.exec();

                ui->loginLineEdit->clear();
                ui->psswdLineEdit->clear();
                ui->whichLine->clear();
            }
            else{
                QMessageBox msgBox;
                msgBox.setWindowTitle("Внимание");
                msgBox.setText("Произошла неизвестная ошибка!");
                msgBox.exec();

                ui->loginLineEdit->clear();
                ui->psswdLineEdit->clear();
                ui->whichLine->clear();
            }
        }
        else if(ui->psswdLineEdit->text() != nullptr && ui->whichLine->text() != nullptr){
            QMessageBox msgBox;
            msgBox.setWindowTitle("Внимание");
            msgBox.setText("Поле с логином не заполнено.");
            msgBox.exec();

            ui->loginLineEdit->clear();
            ui->psswdLineEdit->clear();
            ui->whichLine->clear();
        }
        else if(ui->loginLineEdit->text() != nullptr && ui->psswdLineEdit->text() != nullptr){
            QString login = ui->loginLineEdit->text();
            QString psswd = ui->psswdLineEdit->text();

            QVariantList data;
            data.append(login);
            data.append(psswd);

            db->insertIntoMainTable(data);

            data.clear();

            ui->loginLineEdit->clear();
            ui->psswdLineEdit->clear();
            ui->whichLine->clear();

            QMessageBox _msgBox;
            _msgBox.setWindowTitle("Добавление");
            _msgBox.setText("Пользователь успешно добавлен.");
            _msgBox.exec();

            this->close();
        }
        else if(ui->loginLineEdit->text() != nullptr && ui->whichLine->text() != nullptr){
            QMessageBox msgBox;
            msgBox.setWindowTitle("Внимание");
            msgBox.setText("Поле пароль не заполнено.");
            msgBox.exec();

            ui->loginLineEdit->clear();
            ui->psswdLineEdit->clear();
            ui->whichLine->clear();
        }
        else if(ui->loginLineEdit->text() != nullptr){
            QMessageBox msgBox;
            msgBox.setWindowTitle("Внимание");
            msgBox.setText("Поля пароль и ID не заполнены.");
            msgBox.exec();

            ui->loginLineEdit->clear();
            ui->psswdLineEdit->clear();
            ui->whichLine->clear();
        }
        else if(ui->psswdLineEdit->text() != nullptr){
            QMessageBox msgBox;
            msgBox.setWindowTitle("Внимание");
            msgBox.setText("Поля логин и ID не заполнены.");
            msgBox.exec();

            ui->loginLineEdit->clear();
            ui->psswdLineEdit->clear();
            ui->whichLine->clear();
        }
        else if(ui->whichLine->text() != nullptr){
            QMessageBox msgBox;
            msgBox.setWindowTitle("Внимание");
            msgBox.setText("Поля логин и пароль не заполнены.");
            msgBox.exec();

            ui->loginLineEdit->clear();
            ui->psswdLineEdit->clear();
            ui->whichLine->clear();
        }
        else if(ui->loginLineEdit->text() == nullptr && ui->psswdLineEdit->text() == nullptr &&
                ui->whichLine->text() == nullptr){
            QMessageBox msgBox;
            msgBox.setWindowTitle("Внимание");
            msgBox.setText("Все поля пустые.");
            msgBox.exec();

            ui->loginLineEdit->clear();
            ui->psswdLineEdit->clear();
            ui->whichLine->clear();
        }
        else{
            QMessageBox msgBox;
            msgBox.setWindowTitle("Внимание");
            msgBox.setText("Произошла неизвестная ошибка!");
            msgBox.exec();

            ui->loginLineEdit->clear();
            ui->psswdLineEdit->clear();
            ui->whichLine->clear();
        }
    }
    else if(!db->checkingForIDInWeatherDB(ui->whichLine->text().toInt())){
        QMessageBox::warning(this, "Внимание", "ID не может быть меньше или равно 0.");
    }
    else{
        QMessageBox::warning(this, "Внимание", "Произошла неизвестная ошибка!");
    }
}
