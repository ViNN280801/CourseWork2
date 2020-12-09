#include "deleteweatherrecord.h"
#include "ui_deleteweatherrecord.h"

DeleteWeatherRecord::DeleteWeatherRecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeleteWeatherRecord)
{
    ui->setupUi(this);

    db = new DataBase();
}

DeleteWeatherRecord::~DeleteWeatherRecord()
{
    delete ui;
}

void DeleteWeatherRecord::on_deletePushButton_clicked()
{
    int id = ui->IDLineEdit->text().toInt();

    if(id > 0 && id <= db->checkWeatherDataBaseCountOfRecords()){
        if(ui->IDLineEdit->text() != nullptr){
            db->deleteWeatherRecordByID(id);

            QMessageBox msgBox;
            msgBox.setWindowTitle("Удаление");
            msgBox.setText("Запись была успешно удалена.");
            msgBox.exec();
        }
        else if(ui->IDLineEdit->text() == nullptr){
            QMessageBox::warning(this, "Внимание", "ID не введено");
        }
        else{
            QMessageBox::warning(this, "Внимание", "Произошла неизвестная ошибка!");
        }
    }
    else if(id > db->checkWeatherDataBaseCountOfRecords()){
        QMessageBox::warning(this, "Внимание", "ID не может быть меньше или равно 0.");
    }
    else{
        QMessageBox::warning(this, "Внимание", "Произошла неизвестная ошибка!");
    }

    ui->IDLineEdit->clear();
    this->close();
}

void DeleteWeatherRecord::on_deleteAllPushButton_clicked()
{
    db->deleteAllWeatherRecords();
    db->createWeatherTable();

    QMessageBox msgBox;
    msgBox.setWindowTitle("Удаление всех записей");
    msgBox.setText("Все записи успешно удалены.");
    msgBox.exec();

    this->close();
}
