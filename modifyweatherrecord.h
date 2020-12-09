#ifndef MODIFYWEATHERRECORD_H
#define MODIFYWEATHERRECORD_H

#include <QWidget>
#include <QVariantList>
#include <QMessageBox>

#include "database.h"

namespace Ui {
class ModifyWeatherRecord;
}

class ModifyWeatherRecord : public QWidget
{
    Q_OBJECT

signals:
    void showWindow();

public:
    explicit ModifyWeatherRecord(QWidget *parent = nullptr);
    ~ModifyWeatherRecord();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ModifyWeatherRecord *ui;

    DataBase *db;
};

#endif // MODIFYWEATHERRECORD_H
