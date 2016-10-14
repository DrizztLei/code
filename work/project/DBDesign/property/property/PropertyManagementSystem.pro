#-------------------------------------------------
#
# Project created by QtCreator 2016-09-08T18:27:08
#
#-------------------------------------------------

QT       += core gui sql printsupport network

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PropertyManagementSystem
TEMPLATE = app

CXXFLAGS += gnu+=11


SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
    recordmeterdialog.cpp \
    recordmeterwidget.cpp \
    aboutdialog.cpp \
    contactdialog.cpp \
    setstandardwidget.cpp \
    addchargerwidget.cpp \
    delchargerwidget.cpp \
    delproprietorwidget.cpp \
    addproprietorwidget.cpp \
    userpaywidget.cpp \
    monthbillwidget.cpp \
    monthnotpayedwidget.cpp \
    monthbillreportwidget.cpp \
    seasonbillreportwidget.cpp \
    yearbillreportwidget.cpp \
    allproprietorwidget.cpp \
    allroomproprietor.cpp \
    http.cpp

HEADERS  += mainwindow.h \
    connection.h \
    logindialog.h \
    recordmeterdialog.h \
    recordmeterwidget.h \
    aboutdialog.h \
    contactdialog.h \
    setstandardwidget.h \
    addchargerwidget.h \
    delchargerwidget.h \
    delproprietorwidget.h \
    addproprietorwidget.h \
    userpaywidget.h \
    monthbillwidget.h \
    monthnotpayedwidget.h \
    monthbillreportwidget.h \
    seasonbillreportwidget.h \
    yearbillreportwidget.h \
    allproprietorwidget.h \
    allroomproprietor.h \
    http.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    recordmeterdialog.ui \
    recordmeterwidget.ui \
    aboutdialog.ui \
    contactdialog.ui \
    setstandardwidget.ui \
    addchargerwidget.ui \
    delchargerwidget.ui \
    delproprietorwidget.ui \
    addproprietorwidget.ui \
    userpaywidget.ui \
    monthbillwidget.ui \
    monthnotpayedwidget.ui \
    monthbillreportwidget.ui \
    seasonbillreportwidget.ui \
    yearbillreportwidget.ui \
    allproprietorwidget.ui \
    allroomproprietor.ui \
    authenticationdialog.ui

RESOURCES += \
    icon.qrc
