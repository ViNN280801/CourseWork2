#include "database.h"
#include <QMessageBox>

QVariantList saved;

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase(){
    saved.clear();
}

DataBaseReadMethods::DataBaseReadMethods(QObject *parent) : DataBase(parent)
{

}

DataBaseReadMethods::~DataBaseReadMethods()
{

}

SortMethods::SortMethods(QObject *parent) : DataBaseReadMethods(parent)
{

}

SortMethods::~SortMethods()
{

}

void DataBase::connectToDataBase()
{
    if(!QFile("/home/vladislav/Documents/StudyDocs/"
              "3 semester/IT/Lab3/DataBaseOfUsers/DB/" DATABASE_NAME).exists()){
            this->restoreDataBase();
        } else {
            this->openDataBase();
        }
}

bool DataBase::restoreDataBase()
{
    this->closeWeatherDataBase();

    if(this->openDataBase()){
        if((!this->createMainTable())){
            return false;
        } else {
            return true;
        }
    } else {
        return false;
    }
    return false;
}

bool DataBase::openDataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName("/home/vladislav/Documents/StudyDocs/"
                       "3 semester/IT/Lab3/DataBaseOfUsers/DB/" DATABASE_NAME);
    if(db.open()){
        return true;
    } else {
        return false;
    }

    return false;
}

void DataBase::closeDataBase()
{
    db.close();
}

void DataBase::closeWeatherDataBase()
{
    weather_db.close();
}

bool DataBase::createMainTable()
{
    QSqlQuery query;
    if(!query.exec("CREATE TABLE " TABLE " ("
                            "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                            TABLE_LOGIN " TEXT NOT NULL,"
                            TABLE_PSSWD " TEXT NOT NULL )")){
        return false;
    } else {
        return true;
    }
    return false;
}

bool DataBase::insertIntoMainTable(const QVariantList &data)
{
    this->connectToDataBase();

    QSqlQuery query;
    query.prepare("INSERT INTO " TABLE " ( " TABLE_LOGIN ", "
                                             TABLE_PSSWD ") "
                  "VALUES (:Login, :Password)");
    query.bindValue(":Login", data[0].toString());
    query.bindValue(":Password", data[1].toString());

    if(!query.exec()){
        qDebug() << "error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}


bool DataBase::insertIntoMainTableWithID(const QVariantList &data)
{
    this->connectToDataBase();

    QSqlQuery query;
    query.prepare("INSERT INTO " TABLE " ( " TABLE_LOGIN ", "
                                             TABLE_PSSWD ") "
                  "VALUES (:ID, :Login, :Password)");
    query.bindValue(":ID", data[0].toInt());
    query.bindValue(":Login", data[1].toString());
    query.bindValue(":Password", data[2].toString());

    if(!query.exec()){
        qDebug() << "error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

bool DataBase::insertIntoMainTableWithKnownID(const QVariantList &data, int ID)
{
    this->connectToDataBase();

    if(ID != 1){
        QSqlQuery query;
        query.prepare("INSERT INTO " TABLE " (ID, " TABLE_LOGIN ", " TABLE_PSSWD ")"
                      "VALUES (:ID, :Login, :Password)");
        query.bindValue(":ID", ID);
        query.bindValue(":Login", data[0].toString());
        query.bindValue(":Password", data[1].toString());

        query.exec();

        if(!query.exec()){
            qDebug() << "error insert into " << TABLE;
            qDebug() << query.lastError().text();
            return false;
        } else {
            return true;
        }
    }
    else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("ID не может быть равным 1!");
        msgBox.exec();
    }

    return false;
}

bool DataBase::checkingForIDInWeatherDB(int ID){
    this->connectToWeatherDataBase();

    QString sqlQuery = QString("SELECT " TABLE_WEEKDAY " FROM "
                               TABLE_WEATHER " WHERE ID = '%1'").arg(ID);
    QSqlQuery query;

    query.prepare(sqlQuery);
    query.exec();
    query.next();

    if(query.value(0) != ID)
        return true;
    else return false;
}

bool DataBase::checkingForWeekdayInWeatherDB(QString weekday){
    this->connectToWeatherDataBase();

    QString sqlQuery = QString("SELECT " TABLE_WEEKDAY " FROM "
                               TABLE_WEATHER " WHERE " TABLE_WEEKDAY " = '%1'").arg(weekday);
    QSqlQuery query;

    query.prepare(sqlQuery);
    query.exec();
    query.next();

    if(query.value(0) != weekday)
        return true;
    else return false;
}

bool DataBase::checkingForID(int ID){
    this->connectToDataBase();

    QString sqlQuery = QString("SELECT " TABLE_LOGIN " FROM "
                               TABLE " WHERE ID = '%1'").arg(ID);
    QSqlQuery query;

    query.prepare(sqlQuery);
    query.exec();
    query.next();

    if(query.value(0) != ID)
        return true;
    else return false;
}

bool DataBase::checkingForRecord(QString login){
    this->connectToDataBase();

    QString sqlQuery = QString("SELECT " TABLE_LOGIN " FROM "
                               TABLE " WHERE " TABLE_LOGIN " = '%1'").arg(login);
    QSqlQuery query;

    query.prepare(sqlQuery);
    query.exec();
    query.next();

    if(query.value(0) != login)
        return true;
    else return false;
}

bool DataBase::comparisonMethodIDWithLogin(int ID, QString login){
    this->connectToDataBase();

    QString sqlQuery = QString("SELECT ID, " TABLE_LOGIN " FROM "
                               TABLE " WHERE " TABLE_LOGIN " = '%1'").arg(login);
    QSqlQuery query;

    query.prepare(sqlQuery);
    query.exec();
    query.next();

    if(ID == query.value(0).toInt()){
        return true;
    }
    else return false;

    return false;
}

QString DataBase::checkingForRecordReturningPsswd(QString login){
    this->connectToDataBase();

    QString sqlQuery = QString("SELECT " TABLE_LOGIN " , " TABLE_PSSWD " FROM "
                               TABLE " WHERE " TABLE_LOGIN " = '%1'").arg(login);
    QSqlQuery query;

    query.prepare(sqlQuery);
    query.exec();
    query.next();

    return query.value(1).toString();
}

void DataBase::deleteUserByID(int ID){
    this->connectToDataBase();
    QSqlQuery query;

    QString sqlQuery = QString("DELETE FROM " TABLE
                               " WHERE ID = '%1'").arg(ID);

    query.prepare(sqlQuery);
    query.exec();
}

void DataBase::deleteUserByLogin(QString login){
    this->connectToDataBase();
    QSqlQuery query;

    QString sqlQuery = QString("DELETE FROM " TABLE
                               " WHERE " TABLE_LOGIN " = '%1'")
            .arg(login);

    query.prepare(sqlQuery);
    query.exec();
}

void DataBase::deleteUserByIDAndLogin(int ID, QString login){
    this->connectToDataBase();
    QSqlQuery query;

    QString sqlQuery = QString("DELETE FROM " TABLE
                               " WHERE ID = '%1' AND " TABLE_LOGIN " = '%2'")
            .arg(ID).arg(login);

    query.prepare(sqlQuery);
    query.exec();
}

void DataBase::connectToWeatherDataBase()
{
    if(!QFile("/home/vladislav/Documents/StudyDocs/3 semester/"
              "IT/Lab3/DataBaseOfUsers/DB/" DATABASE_WEATHER_NAME).exists()){
            this->restoreWeatherDataBase();
        } else {
            this->openWeatherDataBase();
        }
}

bool DataBase::restoreWeatherDataBase()
{
    if(this->openWeatherDataBase()){
        if((!this->createWeatherTable())){
            return false;
        } else {
            return true;
        }
    } else {
        return false;
    }
    return false;
}

bool DataBase::openWeatherDataBase()
{
    weather_db = QSqlDatabase::addDatabase("QSQLITE");
    weather_db.setHostName(DATABASE_HOSTNAME_WEATHER);
    weather_db.setDatabaseName("/home/vladislav/Documents/StudyDocs/3 semester"
                       "/IT/Lab3/DataBaseOfUsers/DB/" DATABASE_WEATHER_NAME);

    if(weather_db.open()){
        return true;
    } else {
        return false;
    }

    return false;
}

bool DataBase::createWeatherTable()
{
    this->connectToWeatherDataBase();

    QSqlQuery query;
    if(!query.exec("CREATE TABLE " TABLE_WEATHER
                   "(ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "Weekday DATE NOT NULL,"
                   "Date_ DATE NOT NULL, "
                   "Month DATE NOT NULL, "
                   "Label TEXT NOT NULL, "
                   "Temperature TEXT NOT NULL)")){
        return false;
    } else {
        return true;
    }
    return false;
}

bool DataBase::insertIntoWeatherTable(const QVariantList &data){
    this->connectToWeatherDataBase();

    QSqlQuery query;

    query.prepare("INSERT INTO " TABLE_WEATHER " ( " TABLE_WEEKDAY ", "
                                             TABLE_DATE ", " TABLE_MONTH ", "
                                             TABLE_LABEL ", " TABLE_TEMPERATURE ")"
                  " VALUES (:Weekday, :Date_, :Month, :Label, :Temperature)");
    query.bindValue(":Weekday", data[0].toString());
    query.bindValue(":Date_", data[1].toString());
    query.bindValue(":Month", data[2].toString());
    query.bindValue(":Label", data[3].toString());
    query.bindValue(":Temperature", data[4].toString());

    if(!query.exec()){
        qDebug() << "error insert into " << TABLE_WEATHER;
        return false;
    } else {
        return true;
    }
    return false;
}

bool DataBase::insertIntoWeatherTableWithID(const QVariantList &data, int ID){
    this->connectToWeatherDataBase();

    QSqlQuery query;
    query.prepare("INSERT INTO " TABLE_WEATHER " (ID, " TABLE_WEEKDAY ", "
                                             TABLE_DATE ", " TABLE_MONTH ", "
                                             TABLE_LABEL ", " TABLE_TEMPERATURE ")"
                  " VALUES (:ID, :Weekday, :Date_, :Month, :Label, :Temperature)");
    query.bindValue(":ID", ID);
    query.bindValue(":Weekday", data[0].toString());
    query.bindValue(":Date_", data[1].toString());
    query.bindValue(":Month", data[2].toString());
    query.bindValue(":Label", data[3].toString());
    query.bindValue(":Temperature", data[4].toString());

    query.exec();

    if(!query.exec()){
        qDebug() << "error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }

    return false;
}

bool DataBase::insertIntoWeatherTableWithKnownID(const QVariantList &data, int ID)
{
    this->connectToWeatherDataBase();

    QSqlQuery query;
    query.prepare("INSERT INTO " TABLE_WEATHER " (ID, " TABLE_WEEKDAY ", "
                                             TABLE_DATE ", " TABLE_MONTH ", "
                                             TABLE_LABEL ", " TABLE_TEMPERATURE ")"
                  " VALUES (:ID, :Weekday, :Date_, :Month, :Label, :Temperature)");
    query.bindValue(":ID", ID);
    query.bindValue(":Weekday", data[0].toString());
    query.bindValue(":Date_", data[1].toString());
    query.bindValue(":Month", data[2].toString());
    query.bindValue(":Label", data[3].toString());
    query.bindValue(":Temperature", data[4].toString());

    query.exec();

    if(!query.exec()){
        qDebug() << "error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }

    return false;
}

void DataBase::deleteWeatherRecordByID(int ID){
    this->connectToWeatherDataBase();

    QSqlQuery query;
    QString sqlQuery = QString("DELETE FROM " TABLE_WEATHER
                               " WHERE ID = '%1'").arg(ID);

    query.prepare(sqlQuery);
    query.exec();
}

void DataBase::deleteAllWeatherRecords(){
    this->connectToWeatherDataBase();

    QSqlQuery query;
    query.exec("DELETE FROM " TABLE_WEATHER);
    query.exec("VACUUM");
    query.exec("DROP TABLE " TABLE_WEATHER);
}

void DataBase::modifyWeatherRecordWithID(const QVariantList &data, int ID){
    this->connectToWeatherDataBase();

    QSqlQuery query;

    QString sqlQuery = QString("UPDATE " TABLE_WEATHER
                               " SET " TABLE_WEEKDAY " = '%1', "
                                       TABLE_DATE " = '%2', "
                                       TABLE_MONTH " = '%3', "
                                       TABLE_LABEL " = '%4', "
                                       TABLE_TEMPERATURE " = '%5' "
                               " WHERE ID = %6;")
            .arg(data[0].toString())
            .arg(data[1].toString())
            .arg(data[2].toString())
            .arg(data[3].toString())
            .arg(data[4].toString())
            .arg(ID);

    query.prepare(sqlQuery);
    query.exec();
}

int DataBase::checkUsersDataBaseCountOfRecords(){
    this->connectToDataBase();

    QSqlQuery query;
    QString sqlQuery = QString("SELECT COUNT(*) "
                               " FROM " TABLE);
    query.prepare(sqlQuery);
    query.exec();
    query.next();

    return query.value(0).toInt();
}

int DataBase::checkWeatherDataBaseCountOfRecords(){
    this->connectToWeatherDataBase();

    QSqlQuery query;
    QString sqlQuery = QString("SELECT COUNT(*) "
                               " FROM " TABLE_WEATHER);
    query.prepare(sqlQuery);
    query.exec();
    query.next();

    return query.value(0).toInt();
}

int DataBase::checkWeatherDataBaseCountOfWeekdayRecords(QString weekday){
    this->connectToWeatherDataBase();

    QSqlQuery query;
    QString sqlQuery = QString("SELECT COUNT(*) "
                               " FROM " TABLE_WEATHER
                               " WHERE " TABLE_WEEKDAY " = '%1'").arg(weekday);
    query.prepare(sqlQuery);
    query.exec();
    query.next();

    return query.value(0).toInt();
}

QVariantList DataBaseReadMethods::readDataFromUsersSqlFileToQVariantList(){
    QVariantList data;

    this->connectToDataBase();

    int countOfRecords = this->checkUsersDataBaseCountOfRecords();

    QSqlQuery query;
    QString sqlQuery = QString("SELECT * "
                               "FROM " TABLE);
    query.prepare(sqlQuery);
    query.exec();
    query.next();

    for(int j = 0; j < countOfRecords; j++){
        for(int i = 0; i < 3; i++){
            if(query.value(i + 1).toString() != nullptr)
                data.append(query.value(i + 1));
        }
        query.next();
    }

    return data;
}

QVariantList DataBaseReadMethods::readDataFromWeatherSqlFileToQVariantList(){
    QVariantList data;

    this->connectToWeatherDataBase();

    int countOfRecords = this->checkWeatherDataBaseCountOfRecords();

    QSqlQuery query;
    QString sqlQuery = QString("SELECT * "
                               "FROM " TABLE_WEATHER);
    query.prepare(sqlQuery);
    query.exec();
    query.next();

    for(int j = 0; j < countOfRecords; j++){
        for(int i = 0; i < 6; i++){
            if(query.value(i + 1).toString() != nullptr)
                data.append(query.value(i + 1));
        }
        query.next();
    }

    return data;
}

QVariantList DataBaseReadMethods::readWeekdayFromWeatherSqlFileToQVariantList(QString weekday){
    QVariantList data;

    this->connectToWeatherDataBase();

    int countOfRecords = this->checkWeatherDataBaseCountOfRecords();

    QSqlQuery query;
    QString sqlQuery = QString("SELECT * "
                               "FROM " TABLE_WEATHER
                               " WHERE " TABLE_WEEKDAY " = '%1'").arg(weekday);
    query.prepare(sqlQuery);
    query.exec();
    query.next();

    for(int j = 0; j < countOfRecords; j++){
        for(int i = 0; i < 6; i++){
            if(query.value(i + 1).toString() != nullptr)
                data.append(query.value(i + 1));
        }
        query.next();
    }

    return data;
}

QVariantList DataBaseReadMethods::readDateFromWeatherSqlFileToQVariantList(QString date){
    QVariantList data;

    this->connectToWeatherDataBase();

    int countOfRecords = this->checkWeatherDataBaseCountOfRecords();

    QSqlQuery query;
    QString sqlQuery = QString("SELECT * "
                               "FROM " TABLE_WEATHER
                               " WHERE " TABLE_DATE " = '%1'").arg(date);
    query.prepare(sqlQuery);
    query.exec();
    query.next();

    for(int j = 0; j < countOfRecords; j++){
        for(int i = 0; i < 6; i++){
            if(query.value(i + 1).toString() != nullptr)
                data.append(query.value(i + 1));
        }
        query.next();
    }

    return data;
}

QVariantList DataBaseReadMethods::readMonthFromWeatherSqlFileToQVariantList(QString month){
    QVariantList data;

    this->connectToWeatherDataBase();

    int countOfRecords = this->checkWeatherDataBaseCountOfRecords();

    QSqlQuery query;
    QString sqlQuery = QString("SELECT * "
                               "FROM " TABLE_WEATHER
                               " WHERE " TABLE_MONTH " = '%1'").arg(month);
    query.prepare(sqlQuery);
    query.exec();
    query.next();

    for(int j = 0; j < countOfRecords; j++){
        for(int i = 0; i < 6; i++){
            if(query.value(i + 1).toString() != nullptr)
                data.append(query.value(i + 1));
        }
        query.next();
    }

    return data;
}

void DataBase::backupDataFromWeatherDB(){
    this->connectToWeatherDataBase();
    DataBaseReadMethods *readFromDb = new DataBaseReadMethods();

    QVariantList savedData;

    savedData = readFromDb->readDataFromWeatherSqlFileToQVariantList();
    setSaved(savedData);
}

void DataBase::undoMethod(){
    this->deleteAllWeatherRecords();
    this->createWeatherTable();

    this->connectToWeatherDataBase();

    DataBaseReadMethods *readFromDb = new DataBaseReadMethods();
    QVariantList savedCopy = getSaved();

    for(int i = 1; i <= saved.size(); i++){
        savedCopy.append(saved.value(i - 1));

        if(i % 5 == 0){
            readFromDb->insertIntoWeatherTable(savedCopy);
            savedCopy.clear();
        }
    }

    QMessageBox msgBox;
    msgBox.setWindowTitle("Отмена действий");
    msgBox.setText("Отмена предыдущих действий произошла успешно!");
    msgBox.exec();
}

void DataBase::searchByID(int ID){
    this->backupDataFromWeatherDB();

    QVariantList requiredLine;

    this->connectToWeatherDataBase();

    QSqlQuery query;
    QString sqlQuery = QString("SELECT " TABLE_WEEKDAY ", " TABLE_DATE ", " TABLE_MONTH ", "
                               TABLE_LABEL ", " TABLE_TEMPERATURE
                               " FROM " TABLE_WEATHER
                               " WHERE ID = %1").arg(ID);

    query.prepare(sqlQuery);
    query.exec();
    query.next();

    for(int i = 0; i < 5; i++){
        requiredLine.append(query.value(i));
    }

    this->deleteAllWeatherRecords();
    this->createWeatherTable();
    this->insertIntoWeatherTableWithID(requiredLine, ID);

    requiredLine.clear();
}

void DataBase::searchByWeekday(QString weekday){
    DataBaseReadMethods *read = new DataBaseReadMethods();
    QVariantList weekdayData = read->readWeekdayFromWeatherSqlFileToQVariantList(weekday);
    QVariantList copyData;

    this->backupDataFromWeatherDB();

    this->deleteAllWeatherRecords();
    this->createWeatherTable();

    for(int i = 1; i <= saved.size(); i++){
        copyData.append(weekdayData.value(i - 1));

        if(i % 5 == 0){
            this->insertIntoWeatherTable(copyData);
            copyData.clear();
        }
    }

    weekdayData.clear();
}

void DataBase::searchByDate(QString date){
    DataBaseReadMethods *read = new DataBaseReadMethods();
    QVariantList dateData = read->readDateFromWeatherSqlFileToQVariantList(date);
    QVariantList copyData;

    this->backupDataFromWeatherDB();

    this->deleteAllWeatherRecords();
    this->createWeatherTable();

    for(int i = 1; i <= saved.size(); i++){
        copyData.append(dateData.value(i - 1));

        if(i % 5 == 0){
            this->insertIntoWeatherTable(copyData);
            copyData.clear();
        }
    }

    dateData.clear();
}

void DataBase::searchByMonth(QString month){
    DataBaseReadMethods *read = new DataBaseReadMethods();
    QVariantList dateData = read->readMonthFromWeatherSqlFileToQVariantList(month);
    QVariantList copyData;

    this->backupDataFromWeatherDB();

    this->deleteAllWeatherRecords();
    this->createWeatherTable();

    for(int i = 1; i <= saved.size(); i++){
        copyData.append(dateData.value(i - 1));

        if(i % 5 == 0){
            this->insertIntoWeatherTable(copyData);
            copyData.clear();
        }
    }

    dateData.clear();
}

void DataBase::setSaved(QVariantList savedData){
    saved = savedData;
}

QVariantList DataBase::getSaved(){
    return saved;
}

void SortMethods::sortingByWeekday(){
    QVariantList sortedDataByWeekday;

    this->connectToWeatherDataBase();

    int countOfRecords = this->checkWeatherDataBaseCountOfRecords();

    QSqlQuery query;
    QString sqlQuery = QString(" SELECT * "
                               " FROM " TABLE_WEATHER
                               " ORDER BY " TABLE_WEEKDAY);
    query.prepare(sqlQuery);
    query.exec();
    query.next();

    for(int j = 0; j < countOfRecords; j++){
        for(int i = 0; i < 6; i++){
            if(query.value(i + 1).toString() != nullptr)
                sortedDataByWeekday.append(query.value(i + 1));
        }
        query.next();
    }

    this->backupDataFromWeatherDB();

    this->deleteAllWeatherRecords();
    this->createWeatherTable();

    QVariantList copyData;

    for(int i = 1; i <= saved.size(); i++){
        copyData.append(sortedDataByWeekday.value(i - 1));

        if(i % 5 == 0){
            this->insertIntoWeatherTable(copyData);
            copyData.clear();
        }
    }

    sortedDataByWeekday.clear();

    QMessageBox msgBox;
    msgBox.setWindowTitle("Сортировка по дням недели");
    msgBox.setText("Данные были отсортированы по дням недели.");
    msgBox.exec();
}

void SortMethods::sortingByDate(){
    QVariantList sortedDataByDate;

    this->connectToWeatherDataBase();

    int countOfRecords = this->checkWeatherDataBaseCountOfRecords();

    QSqlQuery query;
    QString sqlQuery = QString(" SELECT * "
                               " FROM " TABLE_WEATHER
                               " ORDER BY " TABLE_DATE);
    query.prepare(sqlQuery);
    query.exec();
    query.next();

    for(int j = 0; j < countOfRecords; j++){
        for(int i = 0; i < 6; i++){
            if(query.value(i + 1).toString() != nullptr)
                sortedDataByDate.append(query.value(i + 1));
        }
        query.next();
    }

    this->backupDataFromWeatherDB();

    this->deleteAllWeatherRecords();
    this->createWeatherTable();

    QVariantList copyData;

    for(int i = 1; i <= saved.size(); i++){
        copyData.append(sortedDataByDate.value(i - 1));

        if(i % 5 == 0){
            this->insertIntoWeatherTable(copyData);
            copyData.clear();
        }
    }

    sortedDataByDate.clear();

    QMessageBox msgBox;
    msgBox.setWindowTitle("Сортировка по дате");
    msgBox.setText("Данные были отсортированы по дате.");
    msgBox.exec();
}

void SortMethods::sortingByMonth(){
    QVariantList sortedDataByMonth;

    this->connectToWeatherDataBase();

    int countOfRecords = this->checkWeatherDataBaseCountOfRecords();

    QSqlQuery query;
    QString sqlQuery = QString(" SELECT * "
                               " FROM " TABLE_WEATHER
                               " ORDER BY " TABLE_MONTH);
    query.prepare(sqlQuery);
    query.exec();
    query.next();

    for(int j = 0; j < countOfRecords; j++){
        for(int i = 0; i < 6; i++){
            if(query.value(i + 1).toString() != nullptr)
                sortedDataByMonth.append(query.value(i + 1));
        }
        query.next();
    }

    this->backupDataFromWeatherDB();

    this->deleteAllWeatherRecords();
    this->createWeatherTable();

    QVariantList copyData;

    for(int i = 1; i <= saved.size(); i++){
        copyData.append(sortedDataByMonth.value(i - 1));

        if(i % 5 == 0){
            this->insertIntoWeatherTable(copyData);
            copyData.clear();
        }
    }

    sortedDataByMonth.clear();

    QMessageBox msgBox;
    msgBox.setWindowTitle("Сортировка по месяцу");
    msgBox.setText("Данные были отсортированы по месяцу.");
    msgBox.exec();
}

void SortMethods::sortingByGeneralCharacteristics(){
    QVariantList sortedDataByGeneralCharacteristics;

    this->connectToWeatherDataBase();

    int countOfRecords = this->checkWeatherDataBaseCountOfRecords();

    QSqlQuery query;
    QString sqlQuery = QString(" SELECT * "
                               " FROM " TABLE_WEATHER
                               " ORDER BY " TABLE_LABEL);
    query.prepare(sqlQuery);
    query.exec();
    query.next();

    for(int j = 0; j < countOfRecords; j++){
        for(int i = 0; i < 6; i++){
            if(query.value(i + 1).toString() != nullptr)
                sortedDataByGeneralCharacteristics.append(query.value(i + 1));
        }
        query.next();
    }

    this->backupDataFromWeatherDB();

    this->deleteAllWeatherRecords();
    this->createWeatherTable();

    QVariantList copyData;

    for(int i = 1; i <= saved.size(); i++){
        copyData.append(sortedDataByGeneralCharacteristics.value(i - 1));

        if(i % 5 == 0){
            this->insertIntoWeatherTable(copyData);
            copyData.clear();
        }
    }

    sortedDataByGeneralCharacteristics.clear();

    QMessageBox msgBox;
    msgBox.setWindowTitle("Сортировка по характеристикам");
    msgBox.setText("Данные были отсортированы по основным характеристикам.");
    msgBox.exec();
}

void SortMethods::sortingByTemperature(){
    QVariantList sortedDataByTempreature;

    this->connectToWeatherDataBase();

    int countOfRecords = this->checkWeatherDataBaseCountOfRecords();

    QSqlQuery query;
    QString sqlQuery = QString(" SELECT * "
                               " FROM " TABLE_WEATHER
                               " ORDER BY " TABLE_TEMPERATURE);
    query.prepare(sqlQuery);
    query.exec();
    query.next();

    for(int j = 0; j < countOfRecords; j++){
        for(int i = 0; i < 6; i++){
            if(query.value(i + 1).toString() != nullptr)
                sortedDataByTempreature.append(query.value(i + 1));
        }
        query.next();
    }

    this->backupDataFromWeatherDB();

    this->deleteAllWeatherRecords();
    this->createWeatherTable();

    QVariantList copyData;

    for(int i = 1; i <= saved.size(); i++){
        copyData.append(sortedDataByTempreature.value(i - 1));

        if(i % 5 == 0){
            this->insertIntoWeatherTable(copyData);
            copyData.clear();
        }
    }

    sortedDataByTempreature.clear();

    QMessageBox msgBox;
    msgBox.setWindowTitle("Сортировка по температуре");
    msgBox.setText("Данные были отсортированы по температуре.");
    msgBox.exec();
}
