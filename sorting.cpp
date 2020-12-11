#include "sorting.h"
#include "ui_sorting.h"

Sorting::Sorting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sorting)
{
    ui->setupUi(this);

    sort = new SortMethods();
}

Sorting::~Sorting()
{
    delete ui;
}

void Sorting::on_sortByWeekdayButton_clicked()
{
    sort->sortingByWeekday();
    this->close();
}

void Sorting::on_sortByDateButton_clicked()
{
    sort->sortingByDate();
    this->close();
}

void Sorting::on_sortByMonth_clicked()
{
    sort->sortingByMonth();
    this->close();
}

void Sorting::on_sortByGenChButton_clicked()
{
    sort->sortingByGeneralCharacteristics();
    this->close();
}

void Sorting::on_sortByTemperature_clicked()
{
    sort->sortingByTemperature();
    this->close();
}
