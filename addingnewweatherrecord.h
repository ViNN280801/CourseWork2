#ifndef ADDINGNEWWEATHERRECORD_H
#define ADDINGNEWWEATHERRECORD_H

#include <QWidget>
#include <QString>
#include <QMessageBox>
#include <QVariantList>

#include "database.h"

namespace Ui {
class AddingNewWeatherRecord;
}

class AddingNewWeatherRecord : public QWidget
{
    Q_OBJECT
signals:
    void showWindow();

public:
    explicit AddingNewWeatherRecord(QWidget *parent = nullptr);
    ~AddingNewWeatherRecord();

private slots:
    void on_addRecordPushButton_clicked();

private:
    Ui::AddingNewWeatherRecord *ui;

    DataBase *db;
};

#endif // ADDINGNEWWEATHERRECORD_H
