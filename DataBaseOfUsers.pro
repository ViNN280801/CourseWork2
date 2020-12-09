QT       += core gui sql

INCLUDEPATH = /usr/include
LIBS += -L/urs/include -lcurl
LIBS += -L/usr/include -lgumbo

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 rtti
PKGCONFIG += curl gumbo

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addingnewweatherrecord.cpp \
    database.cpp \
    deleteuserfromdb.cpp \
    deleteweatherrecord.cpp \
    htmlParser.cpp \
    loginning.cpp \
    main.cpp \
    maindatabase.cpp \
    mainwindow.cpp \
    modifyweatherrecord.cpp \
    searchrecord.cpp \
    usersediditing.cpp

HEADERS += \
    addingnewweatherrecord.h \
    database.h \
    deleteuserfromdb.h \
    deleteweatherrecord.h \
    htmlParser.h \
    htmlThief.h \
    loginning.h \
    maindatabase.h \
    mainwindow.h \
    modifyweatherrecord.h \
    searchrecord.h \
    usersediditing.h

FORMS += \
    addingnewweatherrecord.ui \
    deleteuserfromdb.ui \
    deleteweatherrecord.ui \
    loginning.ui \
    maindatabase.ui \
    mainwindow.ui \
    modifyweatherrecord.ui \
    searchrecord.ui \
    usersediditing.ui

TRANSLATIONS += \
    DataBaseOfUsers_en_IO.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
