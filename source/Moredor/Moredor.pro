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
    guild.cpp \
    race.cpp \
    gamedata.cpp \
    townframe.cpp

HEADERS  += gamewindow.h \
    charactercreationdialog.h \
    guild.h \
    race.h \
    charactermodel.h \
    definitions.h \
    townframe.h \
    gamedata.h

FORMS    += gamewindow.ui \
    charactercreationdialog.ui \
    townframe.ui

RESOURCES += \
    Resources.qrc

CONFIG(release, debug|release) {
    DESTDIR = release
} else {
    DESTDIR = debug
}

#for Windows
win32 {
    #in Windows, you can use & to separate commands
    copyfiles.commands += @echo NOW COPYING ADDITIONAL FILE(S) &
    copyfiles.commands += @call xcopy ..\\..\\assets $${DESTDIR}\\assets /i /Y
}

#for Mac
macx {

}

QMAKE_EXTRA_TARGETS += copyfiles
POST_TARGETDEPS += copyfiles
