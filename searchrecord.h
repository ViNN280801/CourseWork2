#ifndef SEARCHRECORD_H
#define SEARCHRECORD_H

#include <QWidget>
#include <QMessageBox>

#include "database.h"

namespace Ui {
class SearchRecord;
}

class SearchRecord : public QWidget
{
    Q_OBJECT

signals:
    void showWindow();

public:
    explicit SearchRecord(QWidget *parent = nullptr);
    ~SearchRecord();

private slots:
    void on_pushButton_clicked();

    void on_IDradioButton_clicked();

    void on_weekdayRadioButton_clicked();

    void on_dateRadioButton_clicked();

    void on_monthRadioButton_clicked();

    void on_genCharacRadioButton_clicked();

    void on_temperatureRadioButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::SearchRecord *ui;

    DataBase *db;
};

#endif // SEARCHRECORD_H
