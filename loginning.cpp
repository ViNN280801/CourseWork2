#include "loginning.h"
#include "ui_loginning.h"

loginning::loginning(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginning)
{
    ui->setupUi(this);

    mainDB = new MainDataBase();
    connect(mainDB, &MainDataBase::showMainDB, this, &loginning::show);

    db = new DataBase();

    ui->confirmationPsswdLineEdit->hide();
}

loginning::~loginning()
{
    delete ui;
}

void loginning::on_exitButton_clicked()
{
    this->close();
}

void loginning::on_signInButton_clicked()
{
    db->connectToDataBase();

    QSqlQuery query;
    query.exec("DROP TABLE " TABLE_WEATHER);

    MainDataBase *weather_db;
    weather_db = new MainDataBase;

    weather_db->createMainTable();

    ui->confirmationPsswdLineEdit->hide();

    QString login = ui->loginLineEdit->text();
    QString psswd = ui->psswdLineEdit->text();

    QString psswdFromPsswdLineEdit = db->checkingForRecordReturningPsswd(login);

    if(login != nullptr || psswd != nullptr){
        if(login == "admin" && psswd == "admin"){
            QMessageBox msgBox;
            msgBox.setWindowTitle("Вход");
            msgBox.setText("Успешно выполнен вход под Admin.");
            msgBox.exec();

            this->close();

            mainDB->show();
            emit showWindow();
        }
        else{
            if(!db->checkingForRecord(login)){
                if(psswd == psswdFromPsswdLineEdit){
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Вход");
                    msgBox.setText("Вы успешно вошли под пользователем "
                                    + ui->loginLineEdit->text());
                    msgBox.exec();

                    this->close();

                    mainDB->getAddNewButton()->hide();
                    mainDB->getEncodeButton()->hide();
                    mainDB->getDecodeButton()->hide();
                    mainDB->getDeleteButton()->hide();
                    mainDB->getModifyButton()->hide();
                    mainDB->getSearchButton()->show();
                    mainDB->getUndoButton()->show();
                    mainDB->getSortingButton()->show();
                    mainDB->getLabel()->setText("Панель управления пользователя " +
                                                ui->loginLineEdit->text());
                    mainDB->show();
                }
                else if(psswd != psswdFromPsswdLineEdit){
                    QMessageBox::warning(this, "Внимание", "Не найдено ни одного пользователя с "
                                                           "логином " +
                                         ui->loginLineEdit->text() + "!");
                }
                else{
                    QMessageBox::warning(this, "Внимание", "Произошла неизвестная ошибка!");
                }
            }
            else{
                QMessageBox::warning(this, "Внимание", "Не найдено ни одного пользователя с "
                                                       "логином " +
                                     ui->loginLineEdit->text() + "!");
            }
        }
    }
}

void loginning::on_confirmationPsswdLineEdit_editingFinished()
{
    if(ui->psswdLineEdit->text() != ui->confirmationPsswdLineEdit->text()){
        ui->confirmationPsswdLineEdit->setStyleSheet("QLineEdit {"
                                                            "border: 1px solid red;"
                                                            "border-radius: 4px;"
                                                            "}");
    }
}

void loginning::on_signUpButton_clicked()
{
    ui->confirmationPsswdLineEdit->show();

    QSqlQuery query;
    query.exec("DROP TABLE " TABLE_WEATHER);

    MainDataBase *weather_db;
    weather_db = new MainDataBase;

    weather_db->createMainTable();

    QString newLogin = ui->loginLineEdit->text();
    QString newPsswd = nullptr;

    if(ui->confirmationPsswdLineEdit->text() != nullptr){
        if(db->checkingForRecord(newLogin)){
            if(ui->psswdLineEdit->text() == ui->confirmationPsswdLineEdit->text()){
                newPsswd = ui->psswdLineEdit->text();

                QVariantList data;
                data.append(newLogin);
                data.append(newPsswd);
                db->insertIntoMainTable(data);

                data.clear();

                QMessageBox msgBox;
                msgBox.setWindowTitle("Регистрация");
                msgBox.setText("Вы успешно зарегистрировались."
                               " \nВы были добавлены в базу данных пользователей.");
                msgBox.exec();
            }
            else if(ui->psswdLineEdit->text() != ui->confirmationPsswdLineEdit->text()){
                QMessageBox::warning(this, "Внимание", "Passwords don't match, please try again.");
                ui->loginLineEdit->clear();
                ui->psswdLineEdit->clear();
                ui->confirmationPsswdLineEdit->clear();
            }
            else{
                QMessageBox::warning(this, "Внимание", "Произошла неизвестная ошибка!");
            }
        }
        else{
            QMessageBox::warning(this, "Внимание", "Пользователь с таким логином уже существует!");
            ui->loginLineEdit->clear();
            ui->psswdLineEdit->clear();
            ui->confirmationPsswdLineEdit->clear();
        }
    }

    ui->loginLineEdit->clear();
    ui->psswdLineEdit->clear();
    ui->confirmationPsswdLineEdit->clear();
}
