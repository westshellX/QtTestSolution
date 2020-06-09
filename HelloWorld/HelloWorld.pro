TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

#VRCom
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/'../../../Visual Studio 2017/Projects/VRCOM/' -lVRCom
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/'../../../Visual Studio 2017/Projects/VRCOM/' -lVRCom
else:unix: LIBS += -L$$PWD/'../../../Visual Studio 2017/Projects/VRCOM/' -lVRCom

INCLUDEPATH += $$PWD/'../../../Visual Studio 2017/Projects/VRCOM'
DEPENDPATH += $$PWD/'../../../Visual Studio 2017/Projects/VRCOM'

HEADERS += \
    VRComUse.h
