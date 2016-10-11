#-------------------------------------------------
#
# Project created by QtCreator 2016-04-21T16:40:44
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++0x -fpermissive

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia multimediawidgets

TARGET = VLC
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
