TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

unix|win32: LIBS += -L'C:/Program Files (x86)/MySQL/MySQL Connector C 6.1/lib/' -llibmysql

INCLUDEPATH += 'C:/Program Files (x86)/MySQL/MySQL Connector C 6.1/include'
DEPENDPATH += 'C:/Program Files (x86)/MySQL/MySQL Connector C 6.1/include'

DISTFILES += \
    codingLog.txt
