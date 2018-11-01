#-------------------------------------------------
#
# Project created by QtCreator 2016-10-06T21:53:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QMT
TEMPLATE = app


SOURCES += main.cpp\
        mainWindow.cpp \
    spinTime.cpp \
    newStyle.cpp \
    spinSound.cpp \
    playSound.cpp

HEADERS  += mainWindow.h \
    spinTime.h \
    newStyle.h \
    spinSound.h \
    playSound.h

CONFIG += c++14

LIBS += -lportaudio -lsndfile
