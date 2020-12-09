#include "addingnewweatherrecord.h"
#include "ui_addingnewweatherrecord.h"

AddingNewWeatherRecord::AddingNewWeatherRecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddingNewWeatherRecord)
{
    ui->setupUi(this);

    db = new DataBase();
}

AddingNewWeatherRecord::~AddingNewWeatherRecord()
{
    delete ui;
}

void AddingNewWeatherRecord::on_addRecordPushButton_clicked()
{
    QVariantList data;

    QString weekday = ui->weekdayLineEdit->text();
    QString date = ui->dateLineEdit->text();
    QString month = ui->monthLineEdit->text();
    QString label = ui->labelLineEdit->text();
    QString temperature = ui->temperatureLineEdit->text() + "°";
    QString whichLine = ui->whichLineLineEdit->text();

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

    if(db->checkingForIDInWeatherDB(ui->whichLineLineEdit->text().toInt())){
        if(whichLine == nullptr){
            if(weekday != nullptr && date != nullptr && month != nullptr &&
                    label != nullptr && temperature != nullptr){

                db->insertIntoWeatherTable(data);

                QMessageBox msgBox;
                msgBox.setWindowTitle("Добавление");
                msgBox.setText("Новая запись добавлена успешно.");
                msgBox.exec();

                this->close();
            }
            else if(weekday == nullptr && date == nullptr && month == nullptr &&
                    label == nullptr && temperature == nullptr){
                QMessageBox::warning(this, "Внимание", "Не все поля заполнены.");
            }
            else{
                QMessageBox::warning(this, "Внимание", "Произошла неизвестная ошибка!");
            }
        }
        else if(whichLine != nullptr){
            db->insertIntoWeatherTableWithID(data, whichLine.toInt());

            QMessageBox msgBox;
            msgBox.setWindowTitle("Добавление");
            msgBox.setText("Новая запись добавлена успешно.");
            msgBox.exec();

            if(weekday == nullptr && date == nullptr && month == nullptr &&
                    label == nullptr && temperature == nullptr){

                QMessageBox msgBox;
                msgBox.setWindowTitle("Внимание");
                msgBox.setText("Запись с введенным ID уже существует, невозможно заменить.");
                msgBox.exec();
            }
        }
        else{
            QMessageBox::warning(this, "Внимание", "Произошла неизвестная ошибка!");
        }
    }
    else if(!db->checkingForIDInWeatherDB(ui->whichLineLineEdit->text().toInt())){
        QMessageBox::warning(this, "Внимание", "Вы ввели неверный ID записи.");
    }
    else{
        QMessageBox::warning(this, "Внимание", "Произошла неизвестная ошибка!");
    }

    ui->weekdayLineEdit->clear();
    ui->dateLineEdit->clear();
    ui->monthLineEdit->clear();
    ui->labelLineEdit->clear();
    ui->temperatureLineEdit->clear();
    ui->whichLineLineEdit->clear();

    this->close();

    data.clear();
}
