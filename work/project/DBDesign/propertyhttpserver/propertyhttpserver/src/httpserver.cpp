#include "httpserver.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>


#include "../src/database/sql.h"

HttpServer::HttpServer()
{
    qDebug() << "HTTP SERVER INIT .";
}

HttpServer::HttpServer(QCoreApplication *app)
{
    qDebug() << "HTTP SERVER WITH PARAMETER INIT .";
    sem.release();
}

// The request handler receives and responds HTTP requests

void HttpServer::service(HttpRequest& request , HttpResponse& response)
{

    // Get a request parameters
    // QByteArray username = request.getParameter("username");

    sem.acquire(1);

    QByteArray sql = request.getParameter("sql");
    QByteArray length = request.getParameter("length");
    QByteArray commit = request.getParameter("commit");
    QByteArray flag = request.getParameter("flag");
    QByteArray parameter = request.getParameter("parameter");

    qDebug() << "HTTPSERVER : " << request.getParameterMap();

    getSQL()->getQuery()->prepare(sql);
    QString temp = parameter;
    QStringList list = temp.split('\t');

    for(int i = 0 ; i < length.toInt() ; i++)
    {
        getSQL()->getQuery()->addBindValue(list.at(i));
    }

    bool result = getSQL()->getQuery()->exec();

    QByteArray SIZE;
    SIZE.append(QString::number(getSQL()->getQuery()->size()));

    QByteArray ROWS;
    ROWS.append(QString::number(getSQL()->getQuery()->record().count()));

    response.write(SIZE + "\n");
    response.write(ROWS + "\n");

    qDebug() << "GET THE SIZE FOR : " << SIZE;
    qDebug() << "GET THE ROWS FOR : " << ROWS;
    qDebug() << "GET THE RESULT FOR : " << result;

    if(!QString(commit).compare("true"))
    {
        getSQL()->getDatabase()->commit();
    }

    QByteArray sender;
    QString info;

    int size = getSQL()->getQuery()->record().count();

    if(!QString(flag).compare("true"))
    {
        sender.append(QString(result?"true":"false") + "\n");
    }

    while(getSQL()->getQuery()->next())
    {
        for(int i = 0 ; i < size ; i++)
        {
            info = getSQL()->getQuery()->value(i).toString();
            sender.append(info + "\n");
        }
        // sender.append("\n");
    }

    qDebug() << "HTTPSERVER : SEND MESSAGE FOR : " << sender;

    // response.write("<html><body>\n");
    response.write(sender);
    // response.write("</body></html>");

    sem.release(1);
    /*

    getSQL()->getQuery()->prepare(sql);

    QString stringParameter = parameter;
    QStringList list = stringParameter.split('\t');

    for(int i = 0 ; i < length.toInt() ; i++)
    {
        QString value = list.at(i);
        getSQL()->getQuery()->addBindValue(value);
    }

    getSQL()->getQuery()->exec();

    */

    /*

    getSQL()->getQuery()->prepare(sql);
    if(!getSQL()->getQuery()->exec())
    {
        qDebug() << "HTTPSERVER : ERROR FOR EXEC THE QUERY .";

        response.write("HTTPSERVER : ERROR FOR EXEC THE QUERY . ");
        sem.release(1);
        return;
    }

    */

}

HttpServer::~HttpServer()
{
    qDebug() << "HTTP SERVER OVER .";
}

/*
QSqlQuery& HttpServer::operator =(const QSqlQuery& other)
{

    return other;
}
*/

QSqlDatabase* HttpServer::getDatabase()
{
    return this->db;
}

void HttpServer::setDatabase(QSqlDatabase* db)
{
    this->db = db;
}

void HttpServer::setSQL(SQL *point)
{
    this->sql = point;
}

SQL* HttpServer::getSQL()
{
    return this->sql;
}
