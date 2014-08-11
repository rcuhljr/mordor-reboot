#-------------------------------------------------
#
# Project created by QtCreator 2014-08-08T15:43:37
#
#-------------------------------------------------

QT       += core gui designer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Moredor
TEMPLATE = app


SOURCES += main.cpp\
        gamewindow.cpp \
    createcharacterwidget.cpp

HEADERS  += gamewindow.h \
    createcharacterwidget.h

FORMS    += gamewindow.ui \
    createcharacterwidget.ui

RESOURCES += \
    Resources.qrc
