TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    mdataTools.cpp \
    mordorBinaryReader.cpp

HEADERS += \
    mdataTools.hpp \
    mordorBinaryReader.hpp


CONFIG+= MDATA1

MDATA1 {
TARGET = mData1
SOURCES += readMData1.cpp
HEADERS += readMData1.hpp
}

MDATA2 {
TARGET = mData2
SOURCES += readMData2.cpp
HEADERS += readMData2.hpp
}

MDATA3 {
TARGET = mData3
SOURCES += readMData3.cpp
HEADERS += readMData3.hpp
}

MDATA5 {
TARGET = mData5
SOURCES += readMData5.cpp
HEADERS += readMData5.hpp
}

MDATA11 {
TARGET = mData11
SOURCES += readMData11.cpp
HEADERS += readMData11.hpp
}

