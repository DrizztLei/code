#include "src/database/sql.h"

#include <QDebug>

SQL::SQL(QObject *parent) : QObject(parent)
{
    qDebug() << "SQL : SQL INIT .";
}

SQL::~SQL()
{
    qDebug() << "SQL : SQL OVER .";
    db->close();
    delete db;
    delete query;
}

bool SQL::openDatabase(QString database , QString IP, QString databaseType)
{

    db = new QSqlDatabase();

    // db->database(databaseType);

    (*db) = db->addDatabase(databaseType);

    db->setHostName(IP);
    db->setDatabaseName(database);

    /*
    db.setUserName("elvis");
    db.setPassword("Idon'tknow");
    if (!db.open())
    {
        return false;
    }
    */

    return true;
}

bool SQL::logIn(QString userName, QString userPasswd)
{

    db->setUserName(userName);
    db->setPassword(userPasswd);

    if(!db->open())
    {
        return false;
    }
    query = new QSqlQuery();
    return true;
}

QSqlDatabase* SQL::getDatabase()
{
    return db;
}

QSqlQuery* SQL::getQuery()
{
    return query;
}
