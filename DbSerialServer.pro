QT += core network serialport
QT -= gui widgets

DBLIBS +=

TARGET = serialserver

PROJECT_ROOT = ..

SOURCES += main.cpp \
    master.cpp \
    slave.cpp

HEADERS += \
    master.h \
    slave.h

FORMS +=

RESOURCES +=

TRANSLATIONS +=

configinstall.path = $${OUT_PWD}/$${PROJECT_ROOT}/bin
configinstall.files += serialserver.ini
INSTALLS += configinstall

include($${PROJECT_ROOT}/app.pri)
