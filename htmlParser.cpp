#include "htmlParser.h"

int counter = 0, k = 0, j = 0, z = 0, a = 0;

Sinoptik::Sinoptik(){
    std::ofstream copyFile;
    copyFile.open("DataBase.txt", std::ios_base::in);
}

Sinoptik::~Sinoptik(){

}

void Sinoptik::findTemperature(GumboNode *node){
    std::ofstream copyFile;
    copyFile.open("DataBase.txt", std::ios_base::app);

    if(node->type != GUMBO_NODE_ELEMENT)
        return;

    if(node->v.element.tag == GUMBO_TAG_B){
            GumboNode *textBetweenTagB = (GumboNode *)(node->v.element.children.data[0]);
        if(textBetweenTagB->type == GUMBO_NODE_TEXT || textBetweenTagB->type != GUMBO_NODE_WHITESPACE){
            if(z % 2 != 0){
                #ifdef PRNT
                    printf("max = %s\n", textBetweenTagB->v.text.text);
                #endif
                weather[z].temperature = (char *)calloc(strlen(textBetweenTagB->v.text.text), sizeof(char *));
                strcpy(weather[z].temperature, (char *)textBetweenTagB->v.text.text);
                copyFile << weather[z].temperature << " ";
            }
            else{
                #ifdef PRNT
                    printf("min = %s\n", textBetweenTagB->v.text.text);
                #endif
                weather[z].temperature = (char *)calloc(strlen(textBetweenTagB->v.text.text), sizeof(char *));
                strcpy(weather[z].temperature, (char *)textBetweenTagB->v.text.text);
                copyFile << weather[z].temperature << "/";
            }
            z++;
        }
    }

    GumboVector *child = &node->v.element.children;
    for(size_t i = 0; i < (child->length); i++){
        findTemperature((GumboNode *)(child->data[i]));

        if(z == 14){
            i = child->length;
        }
    }

    copyFile.close();
}

void Sinoptik::findLabel(GumboNode *node, const char *lostLabel){
    GumboAttribute  *className;
    std::ofstream copyFile;
    copyFile.open("DataBase.txt", std::ios_base::app);

    if(node->type != GUMBO_NODE_ELEMENT)
        return;

    if(node->v.element.tag == GUMBO_TAG_LABEL &&
        (className = gumbo_get_attribute(&node->v.element.attributes, "class")) &&
        !strcmp(className->value, lostLabel)){
        GumboNode *textBetweenTagLabel = (GumboNode *)(node->v.element.children.data[0]);

        if(textBetweenTagLabel->type == GUMBO_NODE_TEXT
            || textBetweenTagLabel->type != GUMBO_NODE_WHITESPACE){
            std::string tmp = (char *)calloc(strlen(textBetweenTagLabel->v.text.text), sizeof(char *));

            tmp = textBetweenTagLabel->v.text.text;

            for(size_t v = 0; v < tmp.size(); v++){
                if(tmp[v] == ' ')
                    tmp[v] = '_';
            }

            #ifdef PRNT
                printf("%s\n", textBetweenTagLabel->v.text.text);
            #endif

            if(tmp[0] == '\n'){
                tmp[0] = ' ';
            }

            for(size_t v = 0; v < tmp.size(); v++){
                if(tmp[v] == ',' && tmp[v + 1] == ' '){
                    tmp.erase(v, 1);
                    tmp[v + 1] = ' ';
                }
            }

            if(j == 6){
                tmp[tmp.size()] = ' ';
            }

            weather[j].label = (char *)calloc(strlen(textBetweenTagLabel->v.text.text), sizeof(char *));
            strcpy(weather[j].label, tmp.c_str());
            copyFile << weather[j].label;
        }
        j++;
    }
    GumboVector *child = &node->v.element.children;
    for(size_t i = 0; i < (child->length); i++){
        findLabel((GumboNode *)(child->data[i]), lostLabel);
        if(j == 7){
            i = child->length;
        }
    }

    copyFile.close();
}

void Sinoptik::findWeekDay(GumboNode *node, const char *lostWeekDay, const char *curDay){
    GumboAttribute *className;
    std::ofstream copyFile;
    copyFile.open("DataBase.txt", std::ios_base::app);

    if(node->type != GUMBO_NODE_ELEMENT)
        return;

    if(node->v.element.tag == GUMBO_TAG_P &&
        (className = gumbo_get_attribute(&node->v.element.attributes, "class")) &&
        !strcmp(className->value, curDay)){
        GumboNode *textBetweenTagP = (GumboNode *)(node->v.element.children.data[0]);

        if(textBetweenTagP->type == GUMBO_NODE_TEXT || textBetweenTagP->type != GUMBO_NODE_WHITESPACE){
            #ifdef PRNT
                printf("%s\n", textBetweenTagP->v.text.text);
            #endif
            weather[a].weekDay = (char *)calloc(strlen(textBetweenTagP->v.text.text), sizeof(char *));

        if(weather[a].weekDay != NULL && (a == 0 || a == 1)){
            strcpy(weather[a].weekDay, textBetweenTagP->v.text.text);

            copyFile << weather[a].weekDay << " ";
            a++;
            }
        }
    }

    if(node->v.element.tag == GUMBO_TAG_A &&
        (className = gumbo_get_attribute(&node->v.element.attributes, "class")) &&
        !strcmp(className->value, lostWeekDay)){
            GumboNode *textBetweenTagA = (GumboNode *)(node->v.element.children.data[0]);
            if(textBetweenTagA->type == GUMBO_NODE_TEXT || textBetweenTagA->type != GUMBO_NODE_WHITESPACE){
                #ifdef PRNT
                    printf("%s\n", textBetweenTagA->v.text.text);
                #endif
                weather[k+a].weekDay = (char *)calloc(strlen(textBetweenTagA->v.text.text), sizeof(char *));
                strcpy(weather[k+a].weekDay, textBetweenTagA->v.text.text);

                copyFile << weather[k+a].weekDay << " ";
            }
            k++;
            counter++;
    }

    GumboVector *child = &node->v.element.children;
    for(size_t i = 0; i < (child->length); i++){
        findWeekDay((GumboNode *)(child->data[i]), lostWeekDay, curDay);
        if(counter == 7){
            i = child->length;
        }
    }

    copyFile.close();
}

int t = 0, f = 0;

void Sinoptik::findDate(GumboNode *node, const char *lost){
    GumboAttribute *className;
    std::ofstream copyFile;
    copyFile.open("DataBase.txt", std::ios_base::app);

    if(node->type != GUMBO_NODE_ELEMENT)
        return;

    if(node->v.element.tag == GUMBO_TAG_P &&
        (className = gumbo_get_attribute(&node->v.element.attributes, "class")) &&
        !strcmp(className->value, lost)){
        GumboNode *textBetweenTagP = (GumboNode *)(node->v.element.children.data[0]);

        if(textBetweenTagP->type == GUMBO_NODE_TEXT || textBetweenTagP->type != GUMBO_NODE_WHITESPACE){
            #ifdef PRNT
                printf("%s\n", textBetweenTagP->v.text.text);
            #endif
            weather[t].date = (char *)calloc(strlen(textBetweenTagP->v.text.text), sizeof(char *));
            strcpy(weather[t].date, textBetweenTagP->v.text.text);

            if(t != 7)
                copyFile << weather[t].date << " ";
        }
        t++;
    }

    GumboVector *child = &node->v.element.children;
    for(size_t i = 0; i < (child->length); i++){
        findDate((GumboNode *)(child->data[i]), lost);
    }

    copyFile.close();
}

void Sinoptik::findMonth(GumboNode *node, const char *lost){
    GumboAttribute *className;
    std::ofstream copyFile;
    copyFile.open("DataBase.txt", std::ios_base::app);

    if(node->type != GUMBO_NODE_ELEMENT)
        return;

    if(node->v.element.tag == GUMBO_TAG_P &&
        (className = gumbo_get_attribute(&node->v.element.attributes, "class")) &&
        !strcmp(className->value, lost)){
            GumboNode *textBetweenTagP = (GumboNode *)(node->v.element.children.data[0]);

            if(textBetweenTagP->type == GUMBO_NODE_TEXT || textBetweenTagP->type != GUMBO_NODE_WHITESPACE){
                #ifdef PRNT
                    printf("%s\n", textBetweenTagP->v.text.text);
                #endif
                weather[f].month = (char *)calloc(strlen(textBetweenTagP->v.text.text), sizeof(char *));
                strcpy(weather[f].month, textBetweenTagP->v.text.text);

                if(f != 7)
                    copyFile << weather[f].month << " ";
                }
            f++;
    }

    GumboVector *child = &node->v.element.children;
    for(size_t i = 0; i < (child->length); i++){
        findMonth((GumboNode *)(child->data[i]), lost);
    }

    copyFile.close();
}

void Sinoptik::fillWeatherDB(){
    QVariantList saved;
    MainDataBase *db;
    DataBaseReadMethods *readFromDb = new DataBaseReadMethods();

    db = new MainDataBase;
    db->connectToDataBase();

    QSqlQuery query;

    std::fstream file;
    std::string str;
    int countOfSpaces = 0;

    file.open("DataBase.txt", std::ios_base::in);
    if(file.is_open()){
        while(getline(file, str)){}
    }

    for(size_t i = 0 ; i < str.length(); i++){
        if(str[i] == ' ' && str[i + 1] == ' ') {
             k++;
             str.erase(i, 1);
             i--;
        }

        if(str[i] == ' '){
            countOfSpaces++;

            if(countOfSpaces % 7 == 0){
                str[i] = '\n';
            }
        }
    }

    file.close();

    std::ofstream ofs;
    ofs.open("DataBase.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    std::ofstream copyFile;
    copyFile.open("DataBase.txt", std::ios_base::app);
    copyFile << str;
    copyFile.close();

    QVariantList data;
    std::ifstream stream;
    std::string weekday[7], date[7], month[7], label[7], temperature[7];
    QVariant weekday_dest[7], date_dest[7], month_dest[7], label_dest[7], temperature_dest[7];

    stream.open("DataBase.txt", std::ifstream::in);

    for(int i = 0; i < 7; i++){
        stream >> weekday[i];
        weekday_dest[i] = QString::fromStdString(weekday[i]);
    }
    for(int i = 0; i < 7; i++){
        stream >> date[i];
        date_dest[i] = QString::fromStdString(date[i]);
    }
    for(int i = 0; i < 7; i++){
        stream >> month[i];
        month_dest[i] = QString::fromStdString(month[i]);
    }
    for(int i = 0; i < 7; i++){
        stream >> label[i];
        label_dest[i] = QString::fromStdString(label[i]);
    }
    for(int i = 0; i < 7; i++){
        stream >> temperature[i];
        temperature_dest[i] = QString::fromStdString(temperature[i]);
    }

    if(!db->mainDataBaseNotEmpty()){
        for(int i = 0; i < 7; i++){
            data.append(weekday_dest[i]);
            data.append(date_dest[i]);
            data.append(month_dest[i]);
            data.append(label_dest[i]);
            data.append(temperature_dest[i]);

            db->insertIntoMainTable(data);
            data.clear();
        }
    }
    else{
        saved = readFromDb->readDataFromWeatherSqlFileToQVariantList();
        QVariantList savedCopy;
        readFromDb->deleteAllWeatherRecords();
        readFromDb->createWeatherTable();

        for(int i = 1; i <= saved.size(); i++){
            savedCopy.append(saved.value(i - 1));

            if(i % 5 == 0){
                readFromDb->insertIntoWeatherTable(savedCopy);
                savedCopy.clear();
            }
        }
    }

    saved.clear();

    stream.close();
    delete db;
}

int Sinoptik::htmlParse(){
    const char *fileName = "weather.html";
    FILE *fin;
    char *buffer = (char*)calloc(BUFF_SIZE, sizeof(char*));
    char *copy;
    long bytes = 0L;

    if((fin = fopen(fileName, "rb")) == NULL){
        perror("Error: Can't read file. Make sure of existanse this file.");

        return EXIT_FAILURE;
    }

    fseek(fin, 0L, SEEK_END);
    bytes = ftell(fin);
    fseek(fin, 0L, SEEK_SET);

    copy = (char*)calloc(bytes, sizeof(char));

    fseek(fin, 0L, SEEK_SET);

    fread(copy, sizeof(char*), bytes, fin);

    #ifdef PRINT_HTML
         printf("\n%s\n", copy);
         printf("\nSuccessfully read %ld bytes\n", bytes);
    #endif

    free(buffer);

    const char *curDay = "weather__content_tab-day";
    const char *lostWeekDay = "weather__content_tab_a";
    const char *lostDay = "weather__content_tab-date day_red";
    const char *lostMonth = "weather__content_tab-month";
    const char *lostLabel = "show-tooltip";

    GumboOutput *out = gumbo_parse(copy);

    findWeekDay(out->root, lostWeekDay, curDay);
    findDate(out->root, lostDay);
    findMonth(out->root, lostMonth);
    findLabel(out->root, lostLabel);
    findTemperature(out->root);

    gumbo_destroy_output(&kGumboDefaultOptions, out);

    free(copy);
    fclose(fin);

    system(qPrintable("clear"));

    return EXIT_SUCCESS;
}
