QT += core widgets network
QT -= gui

CONFIG += c++11

TARGET = DEMO
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    http.cpp

HEADERS += \
    http.h
