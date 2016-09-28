#include "serialquery.h"

#include <QDebug>
#include <QBuffer>
#include <iostream>

serialQuery::serialQuery(QObject *parent) : QObject(parent)
{
    qDebug() << "SERIALQUERY : INIT .";
}

serialQuery::serialQuery()
{
    qDebug() << "INIT WITHOUT PARMAETER .";
}

void serialQuery::deSerialize(QDataStream &dataStream)
{
    qDebug() << "SERIALQUERY : LOAD .";
    // dataStream >>
}

void serialQuery::serialize(QDataStream &dataStream)
{
    qDebug() << "SERIALQUERY : SAVE .";
    // dataStream << sql;
}

#ifndef QT_NO_DATASTREAM

QDataStream& operator <<(QDataStream& dataStream , const serialQuery& object)
{

    // dataStream << QString(object.metaObject()->className());
    // dataStream << sql;
    // qDebug() << object.metaObject()->className();
    // qDebug() << sizeof(object);
    // qDebug() << memcpy((void*)&dataStream , (void*)&object , sizeof(object));

    /*

    dataStream.resetStatus();

    // serialQuery * holder = new serialQuery();

    QByteArray info;
    QBuffer buff(&info);
    buff.open(QIODevice::ReadWrite);

    memcpy((void *)&buff, (void *)&object, sizeof(object));

    dataStream << info;

    qDebug() << "LENGHT FOR : " << buff.size();
    qDebug() << "LENGHT FOR : " << info.length();

    //buff.close();

    */

    dataStream.resetStatus();

    QByteArray* info = new QByteArray();

    mempcpy((void*)(info) , (void*)(&object) , sizeof(serialQuery));

    /*
    using namespace std;
    cout << info.toStdString() << " FOR INFO ." << endl;
    cout << info.length() << " FOR INFO ." << endl;
    */

    dataStream << (*info);

    return dataStream;
}

QDataStream& operator >>(QDataStream& dataStream , serialQuery& object)
{

    /*
    QString str;
    dataStream >> str;
    object.destroyed();
    if(str == QString("serialQuery"))
    {
        object.load(dataStream);
        return dataStream;
    }
    */

    /*
    QByteArray info;
    QBuffer buff(&info);
    buff.open(QIODevice::ReadOnly);

    dataStream >> holder;

    buff.close();

    serialQuery * holder = new serialQuery();
    memcpy((void *)holder , (void *)&object , sizeof(object));
    */

    /*

    QByteArray info;
    QBuffer buff(&info);

    buff.open(QIODevice::ReadWrite);

    dataStream >> info;

    memcpy((void *)&object, (void *)&buff, sizeof(object));

    qDebug() << "LENGHT FOR : " << buff.size();
    qDebug() << "LENGHT FOR : " << info.length();

    buff.close();

    */

    QByteArray *info = new QByteArray();

    dataStream >> (*info);

    mempcpy((void*)(&object) , (void*)(info) , sizeof(serialQuery));

    return dataStream;

}

#endif

QSqlQuery* serialQuery::getSQL()
{
    return this->sql;
}

void serialQuery::setSQL(QString info)
{

    if(Q_NULLPTR != sql)
    {
        delete sql;
    }

    sql = new QSqlQuery();
    sql->prepare(info);
    this->info = info;
}

QString serialQuery::getInfo()
{
    return this->info;
}

serialQuery::~serialQuery()
{
    if(Q_NULLPTR != sql)
    {
        delete sql;
    }
}
