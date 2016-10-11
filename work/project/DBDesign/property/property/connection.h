#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>

bool createConnection()
{
    // connect to the databases

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("propertydata");

    //db.setUserName("root");
    //db.setPassword("****");

    db.setUserName("elvis");
    db.setPassword("Idon'tknow");

    if (!db.open())
    {
       QMessageBox::critical(0, "Cannot open database","Unable to establisha database connection.", QMessageBox::Cancel);
       return false;
    }
    return true;

    /*
    QSqlQuery query;
    query.exec("select * from building");

    while(query.next())
    {
    // query.value(0)是id的值，将其转换为int型
       QString value0 = query.value(0).toString();
       int value1 = query.value(1).toInt();
       QString value2 = query.value(2).toString();
       //输出两个值
       qDebug() << value0 << value1 <<value2;
    }
    */

    return true;
}

#endif // CONNECTION_H

