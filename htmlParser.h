#ifndef HTMLPARSER_H
#define HTMLPARSER_H

#define BUFF_SIZE 256

#include <QVariantList>
#include <cstdlib>
#include <fstream>
#include <ostream>
#include <iostream>
#include <cctype>
#include <cstring>
#include <sys/stat.h>
#include <gumbo.h>

#include "maindatabase.h"

class Sinoptik{
public:
    struct sinoptik{
        char *weekDay;
        char *date;
        char *month;
        char *label;
        char *temperature;
    };

    struct sinoptik weather[BUFF_SIZE];

public:
    explicit Sinoptik();
    virtual ~Sinoptik();

    void findTemperature(GumboNode *node);
    void findLabel(GumboNode *node, const char *lostLabel);
    void findWeekDay(GumboNode *node, const char *lostWeekDay, const char *curDay);
    void findDate(GumboNode *node, const char *lost);
    void findMonth(GumboNode *node, const char *lost);
    int htmlParse();
    void fillWeatherDB();
};

#endif // HTMLPARSER_H
