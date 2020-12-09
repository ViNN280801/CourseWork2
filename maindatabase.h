#ifndef MAINDATABASE_H
#define MAINDATABASE_H

#define DATABASE_HOSTNAME_WEATHER "WeatherDataBase"
#define DATABASE_WEATHER_NAME "weather.sql"

#define TABLE_WEATHER "Weather"
#define TABLE_WEEKDAY "Weekday"
#define TABLE_DATE "Date_"
#define TABLE_MONTH "Month"
#define TABLE_LABEL "Label"
#define TABLE_TEMPERATURE "Temperature"

#include <QWidget>
#include <QSqlDatabase>
#include <QFile>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

#include "database.h"
#include "addingnewweatherrecord.h"
#include "deleteweatherrecord.h"
#include "modifyweatherrecord.h"
#include "searchrecord.h"

namespace Ui {
class MainDataBase;
}

class MainDataBase : public QWidget
{
    Q_OBJECT

signals:
    void showMainDB();

public:
    int countOfEncryptedWords = 0;
    std::string stringToDecrypt;

    explicit MainDataBase(QWidget *parent = nullptr);
    virtual ~MainDataBase();

    bool createMainTable();
    void connectToDataBase();
    void setupMainModel(const QStringList &headers);
    bool insertIntoMainTable(const QVariantList &data);
    bool mainDataBaseNotEmpty();
    void refreshWindow();
    void createUI();
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    QVariantList EncryptionDecryption();
    void decryptWeatherDB();

    void xor_encryption(const std::string &key, std::string &str);


    QPushButton *getAddNewButton();
    QPushButton *getEncodeButton();
    QPushButton *getDecodeButton();
    QPushButton *getDeleteButton();
    QPushButton *getModifyButton();
    QPushButton *getSearchButton();
    QPushButton *getUndoButton();
    QLabel *getLabel();

private slots:
    void on_exitButton_clicked();

    void on_usersDBpushButton_clicked();

    void on_refreshButton_clicked();

    void on_addNewButton_clicked();

    void on_encodeButton_clicked();

    void on_deleteButton_clicked();

    void on_modifyButton_clicked();

    void on_decodeButton_clicked();

    void on_searchButton_clicked();

    void on_undoPushButton_clicked();

private:
    Ui::MainDataBase *ui;

    QSqlDatabase db;
    DataBase *weatherDB;
    QSqlQueryModel *modelMain;
    AddingNewWeatherRecord *weather;
    DeleteWeatherRecord *deleteWeather;
    ModifyWeatherRecord *modifyRecord;
    SearchRecord *search;

    const char* key = "!#*($U()RI{<#FR#asdgnyu56UH@E#kkI@23FVS-ENJOY";
};

#endif // MAINDATABASE_H
