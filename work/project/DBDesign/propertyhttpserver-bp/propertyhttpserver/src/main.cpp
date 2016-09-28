/**
  @file
  @author Elvis Lei
*/

#include <QCoreApplication>
#include <QDir>

#include <iostream>
#include <string>

#include "httplistener.h"
#include "templatecache.h"
#include "httpsessionstore.h"
#include "staticfilecontroller.h"
#include "filelogger.h"
#include "requestmapper.h"
#include "httpserver.h"
#include "src/database/sql.h"
#include "src/database/serialquery.h"

/** Cache for template files */
TemplateCache* templateCache;

/** Storage for session cookies */
HttpSessionStore* sessionStore;

/** Controller for static files */
StaticFileController* staticFileController;

/** Redirects log messages to a file */
FileLogger* logger;


/** Search the configuration file */
QString searchConfigFile()
{
    QString binDir=QCoreApplication::applicationDirPath();
    QString appName=QCoreApplication::applicationName();
    QString fileName(appName+".ini");

    QStringList searchList;
    searchList.append(binDir);
    searchList.append(binDir+"/etc");
    searchList.append(binDir+"/../etc");
    searchList.append(binDir+"/../../etc"); // for development without shadow build
    searchList.append(binDir+"/../"+appName+"/etc"); // for development with shadow build
    searchList.append(binDir+"/../../"+appName+"/etc"); // for development with shadow build
    searchList.append(binDir+"/../../../"+appName+"/etc"); // for development with shadow build
    searchList.append(binDir+"/../../../../"+appName+"/etc"); // for development with shadow build
    searchList.append(binDir+"/../../../../../"+appName+"/etc"); // for development with shadow build
    searchList.append(QDir::rootPath()+"etc/opt");
    searchList.append(QDir::rootPath()+"etc");

    foreach (QString dir, searchList)
    {
        QFile file(dir+"/"+fileName);
        if (file.exists())
        {
            // found
            fileName=QDir(file.fileName()).canonicalPath();
            qDebug("Using config file %s",qPrintable(fileName));
            return fileName;
        }
    }

    // not found
    foreach (QString dir, searchList)
    {
        qWarning("%s/%s not found",qPrintable(dir),qPrintable(fileName));
    }
    qFatal("Cannot find config file %s",qPrintable(fileName));
    return 0;
}


/**
  Entry point of the program.
*/

/*
int main(int argc, char *argv[])
{
    QCoreApplication app(argc,argv);

    app.setApplicationName("DBServer");
    app.setOrganizationName("Butterfly");

    // Find the configuration file
    QString configFileName=searchConfigFile();

    // Configure logging into a file

    QSettings* logSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
    logSettings->beginGroup("logging");
    FileLogger* logger=new FileLogger(logSettings,10000,&app);
    logger->installMsgHandler();

    // Configure template loader and cache
    QSettings* templateSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
    templateSettings->beginGroup("templates");
    templateCache=new TemplateCache(templateSettings,&app);

    // Configure session store
    QSettings* sessionSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
    sessionSettings->beginGroup("sessions");
    sessionStore=new HttpSessionStore(sessionSettings,&app);

    // Configure static file controller
    QSettings* fileSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
    fileSettings->beginGroup("docroot");
    staticFileController=new StaticFileController(fileSettings,&app);

    // Configure and start the TCP listener
    QSettings* listenerSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
    listenerSettings->beginGroup("listener");
    new HttpListener(listenerSettings,new RequestMapper(&app),&app);

    qWarning("Application has started");moshi

    app.exec();

    qWarning("Application has stopped");
}
*/

/*
  Entry point of the program.
*/

// The main program starts the HTTP server

int main(int argc, char *argv[])
{
    QCoreApplication* app = new QCoreApplication(argc,argv);

    app->setApplicationName("DBServer");

    // app->setOrganizationName("Butterfly");

    // Find the configuration file

    QString configFileName= "/etc/qt/server.ini";

    // Configure logging into a file

    QSettings* settings = new QSettings(configFileName,QSettings::IniFormat,app);

    // Init the sql databases

    SQL* sql = new SQL(Q_NULLPTR);

    if(sql->openDatabase("propertydata"))
    {
        if(sql->logIn("elvis" , "Idon'tknow"))
        {
            qDebug() << "MAIN : LOG IN SUCCESSFUL .";
            /*
            QSqlQuery temp;
            temp.prepare("select * from user");
            temp.exec();
            while(temp.next())
            {
                qDebug() << temp.value(0).toString();
            }
            QSqlQuery h;
            h.prepare("select * from building");
            h.exec();
            while(h.next())
            {
                qDebug() << h.value(0).toString();
            }
            */
        }
        else
        {
            qDebug() << "MAIN : LOG IN FAILED .";
            app->destroyed();
            return EXIT_FAILURE;
        }
    }
    else
    {
        app->destroyed();
        return EXIT_FAILURE;
    }

    settings->beginGroup("listener");

    // QSettings* settings=new QSettings("/home/elvis/Downloads/QT/QtWebApp/Demo1/etc/Demo1.ini",QSettings::IniFormat,app);
    // Init the server

    HttpServer * handler=new HttpServer(app);

    handler->setSQL(sql);
    handler->setDatabase(sql->getDatabase());

    HttpListener* listener=new HttpListener(settings,handler,app);

    //listener->listen();

    return app->exec();
}
