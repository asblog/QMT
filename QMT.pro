#-------------------------------------------------
#
# Project created by QtCreator 2016-10-06T21:53:57
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QMT
TEMPLATE = app


SOURCES += main.cpp\
        mainWindow.cpp \
    spinTime.cpp \
    newStyle.cpp \
    spinSound.cpp

HEADERS  += mainWindow.h \
    spinTime.h \
    newStyle.h \
    spinSound.h

CONFIG += c++14
