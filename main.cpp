#include <QApplication>
#include <QMessageBox>

#include "mainwindow.h"
#include "htmlThief.h"
#include "htmlParser.h"

int main(int argc, char *argv[])
{
    Sinoptik sinoptik;
    QApplication a(argc, argv);
    MainWindow w;
    w.hide();

    QMessageBox msgBox;
    msgBox.setWindowTitle("Копирование");
    msgBox.setText("Успешно скопирована информация с сайта sinoptik.com");
    msgBox.show();

    system(qPrintable("./htmlThief https://sinoptik.com.ru/%D0%BF%D0%BE%"
                          "D0%B3%D0%BE%D0%B4%D0%B0-%D1%81%D0%B0%D0%BD%D0%BA%D"
                          "1%82-%D0%BF%D0%B5%D1%82%D0%B5%D1%80%D0%B1%D1%83%D1%80%D0%B3"));

    sinoptik.htmlParse();
    sinoptik.fillWeatherDB();

    return a.exec();
}
