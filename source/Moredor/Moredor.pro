#-------------------------------------------------
#
# Project created by QtCreator 2014-08-08T15:43:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Moredor
TEMPLATE = app


SOURCES += main.cpp\
        gamewindow.cpp \
    charactercreationdialog.cpp

HEADERS  += gamewindow.h \
    charactercreationdialog.h

FORMS    += gamewindow.ui \
    charactercreationdialog.ui

RESOURCES += \
    Resources.qrc
