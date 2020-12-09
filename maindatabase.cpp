#include "maindatabase.h"
#include "ui_maindatabase.h"

MainDataBase::MainDataBase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainDataBase)
{
    ui->setupUi(this);

    weatherDB = new DataBase();

    this->connectToDataBase();
    this->setupMainModel(QStringList() << "ID" << "День недели" << "Дата" << "Месяц"
                       << "Основные характеристики" << "Температура");
    this->createUI();
    this->closeDataBase();

    weather = new AddingNewWeatherRecord();
    connect(weather, &AddingNewWeatherRecord::showWindow, this, &MainDataBase::show);

    deleteWeather = new DeleteWeatherRecord();
    connect(deleteWeather, &DeleteWeatherRecord::showWindow, this, &MainDataBase::show);

    modifyRecord = new ModifyWeatherRecord();
    connect(modifyRecord, &ModifyWeatherRecord::showWindow, this, &MainDataBase::show);

    ui->decodeButton->setEnabled(false);
    ui->searchButton->hide();
    ui->undoPushButton->hide();

    search = new SearchRecord();
    connect(search, &SearchRecord::showWindow, this, &MainDataBase::show);
}

MainDataBase::~MainDataBase()
{
    delete ui;
}

QPushButton *MainDataBase::getAddNewButton(){
    return ui->addNewButton;
}

QPushButton *MainDataBase::getEncodeButton(){
    return ui->encodeButton;
}

QPushButton *MainDataBase::getDecodeButton(){
    return ui->decodeButton;
}

QPushButton *MainDataBase::getDeleteButton(){
    return ui->deleteButton;
}

QPushButton *MainDataBase::getModifyButton(){
    return ui->modifyButton;
}

QPushButton *MainDataBase::getSearchButton(){
    return ui->searchButton;
}

QPushButton *MainDataBase::getUndoButton(){
    return ui->undoPushButton;
}

QLabel *MainDataBase::getLabel(){
    return ui->label;
}

void MainDataBase::connectToDataBase()
{
    if(!QFile("/home/vladislav/Documents/StudyDocs/"
              "3 semester/IT/Lab3/DataBaseOfUsers/DB/" DATABASE_WEATHER_NAME).exists()){
            this->restoreDataBase();
        } else {
            this->openDataBase();
        }
}

bool MainDataBase::restoreDataBase()
{
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

bool MainDataBase::openDataBase()
{
    this->closeDataBase();

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME_WEATHER);
    db.setDatabaseName("/home/vladislav/Documents/StudyDocs/3 semester/IT/"
                       "Lab3/DataBaseOfUsers/DB/" DATABASE_WEATHER_NAME);
    if(db.open()){
        return true;
    } else {
        return false;
    }
}

void MainDataBase::closeDataBase()
{
    db.close();
}

bool MainDataBase::createMainTable()
{
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

void MainDataBase::on_exitButton_clicked()
{
    this->close();
}

void MainDataBase::setupMainModel(const QStringList &headers)
{
    modelMain = new QSqlQueryModel(this);
    modelMain->setQuery("SELECT * "
                        "FROM " TABLE_WEATHER);

    for(int i = 0, j = 0; i < modelMain->columnCount(); i++, j++){
        modelMain->setHeaderData(i, Qt::Horizontal, headers[j]);
    }
}

void MainDataBase::createUI()
{
    ui->tableView->setModel(modelMain);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}

bool MainDataBase::insertIntoMainTable(const QVariantList &data){
    QSqlQuery query;
    query.prepare("INSERT INTO " TABLE_WEATHER " ( " TABLE_WEEKDAY ", "
                                             TABLE_DATE ", " TABLE_MONTH ", "
                                             TABLE_LABEL ", " TABLE_TEMPERATURE ")"
                  "VALUES (:Weekday, :Date_, :Month, :Label, :Temperature)");
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

void MainDataBase::refreshWindow(){
    this->close();
    this->connectToDataBase();
    this->setupMainModel(QStringList() << "ID" << "День недели" << "Дата" << "Месяц"
                       << "Основные характеристики" << "Температура");
    this->createUI();
    this->show();
}

bool MainDataBase::mainDataBaseNotEmpty(){
    this->connectToDataBase();

    QSqlQuery query;
    QString queryString = QString("SELECT COUNT(*) "
                          "FROM " TABLE_WEATHER);

    query.prepare(queryString);
    query.exec();
    query.next();

    if(query.value(0).toInt() > 0){
        return true;
    }
    else return false;
}

void MainDataBase::on_refreshButton_clicked()
{
    this->refreshWindow();
}

void MainDataBase::on_addNewButton_clicked()
{
    weather->show();
}

void MainDataBase::xor_encryption(const std::string &key, std::string &str){
    for(size_t i = 0; i != str.length(); i++)
        str[i] ^= key[i % key.size()];
}

QVariantList MainDataBase::EncryptionDecryption(){
    QVariantList encryptedData;
    DataBaseReadMethods *readFromDB = new DataBaseReadMethods();

    QVariantList data = readFromDB->readDataFromWeatherSqlFileToQVariantList();
    std::string str;
    int countOfSpaces = 0;

    for(int i = 0; i < data.size(); i++){
        str.append(data.value(i).toString().toStdString());
        str.append(" ");
    }

    for(size_t i = 0; i < str.length(); i++){
        if(str[i] == ' '){
            countOfSpaces++;

            if(countOfSpaces % 5 == 0){
                str[i] = '\n';

                if(str[i - 1] == ' ')
                    str.erase(i - 1, 1);
            }
        }
    }

    stringToDecrypt = str;

    std::stringstream strStream(str);
    std::string word;
    QVariant wordQVariant;

    weatherDB->deleteAllWeatherRecords();
    weatherDB->createWeatherTable();

    countOfEncryptedWords = countOfSpaces;

    for(int i = 1; i <= countOfEncryptedWords; i++){
        strStream >> word;
        this->xor_encryption(key, word);

        wordQVariant = QString::fromStdString(word);

        encryptedData.append(wordQVariant);

        if(i % 5 == 0){
            weatherDB->insertIntoWeatherTable(encryptedData);
            encryptedData.clear();
        }
    }

    QMessageBox msgBox;
    msgBox.setWindowTitle("Шифрование");
    msgBox.setText("Информация успешно зашифрована!");
    msgBox.exec();

    ui->addNewButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);
    ui->modifyButton->setEnabled(false);
    ui->encodeButton->setEnabled(false);
    ui->decodeButton->setEnabled(true);

    this->refreshWindow();

    delete readFromDB;

    return encryptedData;
}

void MainDataBase::on_encodeButton_clicked()
{
    this->EncryptionDecryption();
    this->refreshWindow();
}

void MainDataBase::on_deleteButton_clicked()
{
    deleteWeather->show();
}

void MainDataBase::on_modifyButton_clicked()
{
    modifyRecord->show();
}

void MainDataBase::decryptWeatherDB(){
    std::stringstream strStream(stringToDecrypt);
    DataBaseReadMethods *readFromDB = new DataBaseReadMethods();
    QVariantList encryptedData = readFromDB->readDataFromWeatherSqlFileToQVariantList();

    QVariantList decryptedData;

    QString qstr;
    QVariant qvar;
    std::string str;

    weatherDB->deleteAllWeatherRecords();
    weatherDB->createWeatherTable();

    for(int i = 1; i <= countOfEncryptedWords; i++){
        strStream >> stringToDecrypt;
        str = stringToDecrypt;

        this->xor_encryption(key, str);
        this->xor_encryption(key, str);

        qstr = QString::fromStdString(str);
        qvar = qstr;

        qvar = QString::fromStdString(str);

        decryptedData.append(qvar);

        if(i % 5 == 0){
            weatherDB->insertIntoWeatherTable(decryptedData);
            decryptedData.clear();
        }
    }

    QMessageBox msgBox;
    msgBox.setWindowTitle("Дешифрование");
    msgBox.setText("Информация успешно дешифрована!");
    msgBox.exec();

    ui->addNewButton->setEnabled(true);
    ui->deleteButton->setEnabled(true);
    ui->modifyButton->setEnabled(true);
    ui->encodeButton->setEnabled(true);
    ui->decodeButton->setEnabled(false);

    delete readFromDB;
}

void MainDataBase::on_decodeButton_clicked()
{
    this->decryptWeatherDB();
    this->refreshWindow();
}

void MainDataBase::on_searchButton_clicked()
{
    search->show();
    ui->undoPushButton->setEnabled(true);
}
void MainDataBase::on_undoPushButton_clicked()
{
    weatherDB->undoMethod();
}
