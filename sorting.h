#ifndef SORTING_H
#define SORTING_H

#include <QWidget>

#include "database.h"

namespace Ui {
class Sorting;
}

class Sorting : public QWidget
{
    Q_OBJECT

signals:
    void showWindow();

public:
    explicit Sorting(QWidget *parent = nullptr);
    ~Sorting();

private slots:
    void on_sortByWeekdayButton_clicked();

    void on_sortByDateButton_clicked();

    void on_sortByMonth_clicked();

    void on_sortByGenChButton_clicked();

    void on_sortByTemperature_clicked();

private:
    Ui::Sorting *ui;

    SortMethods *sort;
};

#endif // SORTING_H
