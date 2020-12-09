#ifndef DELETEWEATHERRECORD_H
#define DELETEWEATHERRECORD_H

#include <QWidget>
#include <QSqlQuery>
#include <QMessageBox>
#include <QLineEdit>

#include "database.h"

namespace Ui {
class DeleteWeatherRecord;
}

class DeleteWeatherRecord : public QWidget
{
    Q_OBJECT

public:
    explicit DeleteWeatherRecord(QWidget *parent = nullptr);
    ~DeleteWeatherRecord();

signals:
    void showWindow();

private slots:
    void on_deletePushButton_clicked();

    void on_deleteAllPushButton_clicked();

private:
    Ui::DeleteWeatherRecord *ui;

    DataBase *db;
};

#endif // DELETEWEATHERRECORD_H
