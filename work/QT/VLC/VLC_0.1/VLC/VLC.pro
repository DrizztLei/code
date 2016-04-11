#-------------------------------------------------
#
# Project created by QtCreator 2016-04-11T10:11:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VLC
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    newspaper.h \
    reader.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++0x
QT += network
QT += sql
QT += testlib
