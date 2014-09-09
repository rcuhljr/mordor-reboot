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
    charactercreationdialog.cpp \
    creationlogic.cpp \
    guild.cpp \
    race.cpp

HEADERS  += gamewindow.h \
    charactercreationdialog.h \
    creationlogic.h \
    guild.h \
    race.h \
    charactermodel.h \
    definitions.h

FORMS    += gamewindow.ui \
    charactercreationdialog.ui

RESOURCES += \
    Resources.qrc

# Adding debug to the path is a hack until we can dynamically load resources
assets.path = $$OUT_PWD/debug/assets
assets.files = ../../assets/*
INSTALLS += assets
