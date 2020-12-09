#include "modifyweatherrecord.h"
#include "ui_modifyweatherrecord.h"

ModifyWeatherRecord::ModifyWeatherRecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyWeatherRecord)
{
    ui->setupUi(this);

    db = new DataBase();
}

ModifyWeatherRecord::~ModifyWeatherRecord()
{
    delete ui;
}

void ModifyWeatherRecord::on_pushButton_clicked()
{
    QVariantList data;

    QString weekday = ui->weekdayLineEdit->text();
    QString date = ui->dateLineEdit->text();
    QString month = ui->monthLineEdit->text();
    QString label = ui->labelLineEdit->text();
    QString temperature = ui->temperatureLineEdit->text() + "°";
    int id = ui->IDLineEdit->text().toInt();

    for(int i = 0; i < weekday.length(); i++){
        if(weekday[i] == ' ')
            weekday[i] = '_';
    }
    for(int i = 0; i < date.length(); i++){
        if(date[i] == ' ')
            date[i] = '_';
    }
    for(int i = 0; i < month.length(); i++){
        if(month[i] == ' ')
            month[i] = '_';
    }
    for(int i = 0; i < label.length(); i++){
        if(label[i] == ' ')
            label[i] = '_';
    }
    for(int i = 0; i < temperature.length(); i++){
        if(temperature[i] == ' ')
            temperature[i] = '_';
    }

    data.append(weekday);
    data.append(date);
    data.append(month);
    data.append(label);
    data.append(temperature);

    if(db->checkingForIDInWeatherDB(id)){
        if(weekday == nullptr || date == nullptr || month == nullptr ||
                label == nullptr || temperature == nullptr || ui->IDLineEdit->text() == nullptr){
            QMessageBox::warning(this, "Внимание", "Некоторые поля не заполнены.");
        }
        else if(weekday != nullptr && date != nullptr && month != nullptr &&
                label != nullptr && temperature != nullptr && ui->IDLineEdit->text() != nullptr){
            db->modifyWeatherRecordWithID(data, id);

            QMessageBox msgBox;
            msgBox.setWindowTitle("Изменение");
            msgBox.setText("Запись была успешно изменена.");
            msgBox.exec();
        }
        else{
            QMessageBox::warning(this, "Внимание", "Произошла неизвестная ошибка!");
        }
    }
    else if(!db->checkingForIDInWeatherDB(id)){
        QMessageBox::warning(this, "Внимание", "Вы ввели неверный ID.");
    }
    else{
        QMessageBox::warning(this, "Внимание", "Произошла неизвестная ошибка!");
    }

    ui->IDLineEdit->clear();
    ui->weekdayLineEdit->clear();
    ui->dateLineEdit->clear();
    ui->monthLineEdit->clear();
    ui->labelLineEdit->clear();
    ui->temperatureLineEdit->clear();

    data.clear();

    this->close();
}
