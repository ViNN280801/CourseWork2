#include "deleteuserfromdb.h"
#include "ui_deleteuserfromdb.h"

deleteUserFromDB::deleteUserFromDB(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::deleteUserFromDB)
{
    ui->setupUi(this);

    db = new DataBase();
}

deleteUserFromDB::~deleteUserFromDB()
{
    delete ui;
}

void deleteUserFromDB::on_pushButton_clicked()
{
    if(db->checkingForID(ui->IDLineEdit->text().toInt())){
        if(ui->deleteLoginLineEdit->text() != nullptr){
            db->deleteUserByLogin(ui->deleteLoginLineEdit->text());

            QMessageBox msgBox;
            msgBox.setWindowTitle("Удаление");
            msgBox.setText("Пользователь успешно удален.");
            msgBox.exec();

            ui->deleteLoginLineEdit->clear();
            ui->IDLineEdit->clear();
        }
        else if(ui->IDLineEdit->text() != nullptr){
            if(ui->IDLineEdit->text().toInt() != 1){
                db->deleteUserByID(ui->IDLineEdit->text().toInt());

                QMessageBox msgBox;
                msgBox.setWindowTitle("Удаление");
                msgBox.setText("Пользователь успешно удален.");
                msgBox.exec();

                ui->deleteLoginLineEdit->clear();
                ui->IDLineEdit->clear();
            }
            else if(ui->IDLineEdit->text().toInt() == 1){
                QMessageBox msgBox;
                msgBox.setWindowTitle("Внимание");
                msgBox.setText("Невозможно удалить запись ID которого равен 1!");
                msgBox.exec();

                ui->deleteLoginLineEdit->clear();
                ui->IDLineEdit->clear();
            }
            else{
                QMessageBox::warning(this, "Внимание", "Произошла неизвестная ошибка");
            }
        }
        else if(ui->deleteLoginLineEdit->text() != nullptr && ui->IDLineEdit->text() != nullptr){
            if(ui->IDLineEdit->text().toInt() != 1){
                if(db->comparisonMethodIDWithLogin(ui->IDLineEdit->text().toInt(),
                                                ui->deleteLoginLineEdit->text())){
                    db->deleteUserByIDAndLogin(ui->IDLineEdit->text().toInt(),
                                               ui->deleteLoginLineEdit->text());

                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Удаление");
                    msgBox.setText("Пользователь успешно удален.");
                    msgBox.exec();

                    ui->deleteLoginLineEdit->clear();
                    ui->IDLineEdit->clear();
                }
                else if(!db->comparisonMethodIDWithLogin(ui->IDLineEdit->text().toInt(),
                                                        ui->deleteLoginLineEdit->text())){
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Внимание");
                    msgBox.setText("ID и логин не совпадают с записью.");
                    msgBox.exec();

                    ui->deleteLoginLineEdit->clear();
                    ui->IDLineEdit->clear();
                }
                else{
                    QMessageBox::warning(this, "Внимание", "Произошла неизвестная ошибка");
                }
            }
            else if(ui->IDLineEdit->text().toInt() == 1){
                QMessageBox msgBox;
                msgBox.setWindowTitle("Внимание");
                msgBox.setText("Невозможно удалить запись ID которого равен 1!");
                msgBox.exec();

                ui->deleteLoginLineEdit->clear();
                ui->IDLineEdit->clear();
            }
            else{
                QMessageBox::warning(this, "Внимание", "Произошла неизвестная ошибка");
            }
        }
        else{
            QMessageBox::warning(this, "Внимание", "Произошла неизвестная ошибка");
        }
    }
    else{
        QMessageBox::warning(this, "Внимание", "Произошла неизвестная ошибка");
    }

    this->close();
}

void deleteUserFromDB::on_pushButton_2_clicked()
{
    db->connectToDataBase();
    QSqlQuery query;
    query.exec("DROP TABLE " TABLE);
    db->createMainTable();
    db->closeDataBase();

    QVariantList data;
    data.append("admin");
    data.append("admin");
    db->insertIntoMainTable(data);
    data.clear();

    QMessageBox msgBox;
    msgBox.setWindowTitle("Удаление всех записей");
    msgBox.setText("Все записи успешно удалены, за исключением записи,"
                   " содержащей в себе привилегилированного пользователя.");
    msgBox.exec();

    ui->deleteLoginLineEdit->clear();
    ui->IDLineEdit->clear();

    this->close();
}
