#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

#include <ctime>

#define DATABASE_HOSTNAME "UsersDataBase"
#define DATABASE_NAME "users.sql"

#define TABLE "Users"
#define TABLE_LOGIN "Login"
#define TABLE_PSSWD "Password"

#define DATABASE_HOSTNAME_WEATHER "WeatherDataBase"
#define DATABASE_WEATHER_NAME "weather.sql"

#define TABLE_WEATHER "Weather"
#define TABLE_WEEKDAY "Weekday"
#define TABLE_DATE "Date_"
#define TABLE_MONTH "Month"
#define TABLE_LABEL "Label"
#define TABLE_TEMPERATURE "Temperature"

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    virtual ~DataBase();

    bool createMainTable();
    void connectToDataBase();
    bool insertIntoMainTable(const QVariantList &data);
    bool insertIntoMainTableWithID(const QVariantList &data);
    bool insertIntoMainTableWithKnownID(const QVariantList &data, int ID);
    bool checkingForRecord(QString login);
    bool checkingForID(int ID);
    bool comparisonMethodIDWithLogin(int ID, QString login);
    void deleteUserByID(int ID);
    void deleteUserByLogin(QString login);
    void deleteUserByIDAndLogin(int ID, QString login);
    QString checkingForRecordReturningPsswd(QString login);
    int checkUsersDataBaseCountOfRecords();

    bool checkingForIDInWeatherDB(int ID);
    bool checkingForWeekdayInWeatherDB(QString weekday);
    bool insertIntoWeatherTable(const QVariantList &data);
    bool insertIntoWeatherTableWithID(const QVariantList &data, int ID);
    bool insertIntoWeatherTableWithKnownID(const QVariantList &data, int ID);
    bool openWeatherDataBase();
    bool createWeatherTable();
    bool restoreWeatherDataBase();
    void connectToWeatherDataBase();
    void deleteWeatherRecordByID(int ID);
    void deleteAllWeatherRecords();
    void modifyWeatherRecordWithID(const QVariantList &data, int ID);
    int checkWeatherDataBaseCountOfRecords();
    int checkWeatherDataBaseCountOfWeekdayRecords(QString weekday);

    void backupDataFromWeatherDB();
    void undoMethod();
    void searchByID(int ID);
    void searchByWeekday(QString weekday);
    void searchByDate(QString date);
    void searchByMonth(QString month);

    void closeDataBase();
    void closeWeatherDataBase();

    void setSaved(QVariantList savedData);
    QVariantList getSaved();

private:
    QSqlDatabase db;
    QSqlDatabase weather_db;

private:
    bool openDataBase();
    bool restoreDataBase();
};

class DataBaseReadMethods : public DataBase{
    Q_OBJECT
public:
    explicit DataBaseReadMethods(QObject *parent = 0);
    virtual ~DataBaseReadMethods();

    QVariantList readDataFromWeatherSqlFileToQVariantList();
    QVariantList readDataFromUsersSqlFileToQVariantList();
    QVariantList readWeekdayFromWeatherSqlFileToQVariantList(QString weekday);
    QVariantList readDateFromWeatherSqlFileToQVariantList(QString date);
    QVariantList readMonthFromWeatherSqlFileToQVariantList(QString month);
};

#endif // DATABASE_H
