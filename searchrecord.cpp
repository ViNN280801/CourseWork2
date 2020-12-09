#include "searchrecord.h"
#include "ui_searchrecord.h"

SearchRecord::SearchRecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchRecord)
{
    ui->setupUi(this);

    db = new DataBase();
}

SearchRecord::~SearchRecord()
{
    delete ui;
}

void SearchRecord::on_pushButton_clicked()
{
    if(ui->IDLineEdit->text() != nullptr && ui->IDradioButton->isChecked() == true){
        if(db->checkingForIDInWeatherDB(ui->IDLineEdit->text().toInt())){
            db->searchByID(ui->IDLineEdit->text().toInt());

            QMessageBox msgBox;
            msgBox.setWindowTitle("Поиск по ID");
            msgBox.setText("Поиск по ID произведён.");
            msgBox.exec();
        }
        else{
            QMessageBox msgBox;
            msgBox.setWindowTitle("Поиск по ID");
            msgBox.setText("Не найдено записи с таким ID.");
            msgBox.exec();
        }
    }
    else if(ui->IDradioButton->isChecked() == true)
        QMessageBox::warning(this, "Внимание", "Поле ID пустое!");

    if(ui->weekdayLineEdit->text() != nullptr && ui->weekdayRadioButton->isChecked() == true){
        if(!db->checkingForWeekdayInWeatherDB(ui->weekdayLineEdit->text())){
            db->searchByWeekday(ui->weekdayLineEdit->text());

            QMessageBox msgBox;
            msgBox.setWindowTitle("Поиск по дню недели");
            msgBox.setText("Поиск по дню недели произведён.");
            msgBox.exec();
        }
        else{
            QMessageBox msgBox;
            msgBox.setWindowTitle("Поиск по дню недели");
            msgBox.setText("Не найдено записи с таким днем недели.");
            msgBox.exec();
        }
    }
    else if(ui->weekdayRadioButton->isChecked() == true)
        QMessageBox::warning(this, "Внимание", "Поле День Недели пустое!");

    if(ui->dateLineEdit->text() != nullptr && ui->dateRadioButton->isChecked() == true){
        db->searchByDate(ui->dateLineEdit->text());

        QMessageBox msgBox;
        msgBox.setWindowTitle("Поиск по дате");
        msgBox.setText("Поиск по дате произведён.");
        msgBox.exec();
    }
    else if(ui->dateRadioButton->isChecked() == true)
        QMessageBox::warning(this, "Внимание", "Поле Дата пустое!");

    if(ui->monthLineEdit->text() != nullptr && ui->monthRadioButton->isChecked() == true){
        db->searchByMonth(ui->monthLineEdit->text());

        QMessageBox msgBox;
        msgBox.setWindowTitle("Поиск по месяцу");
        msgBox.setText("Поиск по месяцу произведён.");
        msgBox.exec();
    }
    else if(ui->monthRadioButton->isChecked() == true)
        QMessageBox::warning(this, "Внимание", "Поле Месяц пустое!");

    ui->IDLineEdit->clear();
    ui->dateLineEdit->clear();
    ui->monthLineEdit->clear();
    ui->weekdayLineEdit->clear();

    this->close();
}

void SearchRecord::on_IDradioButton_clicked()
{
    ui->IDLineEdit->setEnabled(true);

    ui->weekdayRadioButton->setEnabled(false);
    ui->dateRadioButton->setEnabled(false);
    ui->monthRadioButton->setEnabled(false);
}

void SearchRecord::on_weekdayRadioButton_clicked()
{
    ui->weekdayLineEdit->setEnabled(true);

    ui->IDradioButton->setEnabled(false);
    ui->dateRadioButton->setEnabled(false);
    ui->monthRadioButton->setEnabled(false);
}

void SearchRecord::on_dateRadioButton_clicked()
{
    ui->dateLineEdit->setEnabled(true);

    ui->weekdayRadioButton->setEnabled(false);
    ui->IDradioButton->setEnabled(false);
    ui->monthRadioButton->setEnabled(false);
}

void SearchRecord::on_monthRadioButton_clicked()
{
    ui->monthLineEdit->setEnabled(true);

    ui->weekdayRadioButton->setEnabled(false);
    ui->dateRadioButton->setEnabled(false);
    ui->IDradioButton->setEnabled(false);
}

void SearchRecord::on_pushButton_2_clicked()
{
    ui->IDradioButton->setDisabled(true);
    ui->weekdayRadioButton->setDisabled(true);
    ui->dateRadioButton->setDisabled(true);
    ui->monthRadioButton->setDisabled(true);

    ui->IDradioButton->setEnabled(true);
    ui->weekdayRadioButton->setEnabled(true);
    ui->dateRadioButton->setEnabled(true);
    ui->monthRadioButton->setEnabled(true);

    ui->IDLineEdit->setEnabled(false);
    ui->weekdayLineEdit->setEnabled(false);
    ui->dateLineEdit->setEnabled(false);
    ui->monthLineEdit->setEnabled(false);
}
