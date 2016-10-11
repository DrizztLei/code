# This project demonstrates how to use QtWebAppLib by including the
# sources into this project.

TARGET = propertyhttpserver
TEMPLATE = app
QT += core network sql
CONFIG += console

HEADERS += \
           src/requestmapper.h \
           src/controller/dumpcontroller.h \
           src/controller/templatecontroller.h \
           src/controller/formcontroller.h \
           src/controller/fileuploadcontroller.h \
           src/controller/sessioncontroller.h \
    src/httpserver.h \
    src/database/sql.h \
    src/database/serialquery.h

SOURCES += src/main.cpp \
           src/requestmapper.cpp \
           src/controller/dumpcontroller.cpp \
           src/controller/templatecontroller.cpp \
           src/controller/formcontroller.cpp \
           src/controller/fileuploadcontroller.cpp \
           src/controller/sessioncontroller.cpp \
    src/httpserver.cpp \
    src/database/sql.cpp \
    src/database/serialquery.cpp

#OTHER_FILES += etc/* etc/docroot/* etc/templates/* etc/ssl/* logs/* ../readme.txt
OTHER_FILES += etc/* etc/docroot/* etc/templates/* etc/ssl/* logs/*

#---------------------------------------------------------------------------------------
# The following lines include the sources of the QtWebAppLib library
#---------------------------------------------------------------------------------------

#include(../QtWebApp/logging/logging.pri)
include(../logging/logging.pri)
#include(../QtWebApp/httpserver/httpserver.pri)
include(../httpserver/httpserver.pri)
#include(../QtWebApp/templateengine/templateengine.pri)
include(../templateengine/templateengine.pri)
# Not used: include(../QtWebApp/qtservice/qtservice.pri)
