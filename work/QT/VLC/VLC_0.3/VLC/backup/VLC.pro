#-------------------------------------------------
#
# Project created by QtCreator 2016-04-19T09:26:55
#
#-------------------------------------------------

QT       += core gui network xml multimedia multimediawidgets widgets
QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network xml multimedia multimediawidgets widgets

TARGET = VLC
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    histogramwidget.h \
    player.h

FORMS    += mainwindow.ui

maemo *{
    DEFINES += PLAYER_NO_COLOROPTIONS
}

target.path = $$[QT_INSTALL_EXAMPLES]/multimediawidgets/player
INSTALL += target
