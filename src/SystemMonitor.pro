#-------------------------------------------------
#
# Project created by QtCreator 2011-02-09T00:22:45
#
#-------------------------------------------------

QT       += core gui

TARGET = SysResourceMoniter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    powerInfo.cpp \
    advancedoptions.cpp

HEADERS  += mainwindow.h \
    powerInfo.h \
    advancedoptions.h

INCLUDEPATH += /usr/include/glib-2.0/
INCLUDEPATH += /usr/lib/glib-2.0/include/
INCLUDEPATH += /usr/include/libgtop-2.0/

LIBS += -lgtop-2.0

FORMS    += mainwindow.ui \
    advancedoptions.ui
