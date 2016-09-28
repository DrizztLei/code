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
    QByteArray commit = request.getParameter("commit");
    QByteArray flag = request.getParameter("flag");

    qDebug() << "HTTPSERVER : GET INFO : " << sql;

    getSQL()->getQuery()->exec(temp);

    QByteArray sender;
    QString info;

    int size = getSQL()->getQuery()->record().count();

    while(getSQL()->getQuery()->next())
    {
        for(int i = 0 ; i < size ; i++)
        {
            info = getSQL()->getQuery()->value(i).toString();
            sender.append(info + "\t");
        }
        sender.append("\n");
    }

    // Set a response header
    // response.setHeader("Content-Type", "text/html; charset=ISO-8859-1");
    //response.setHeader("Content-Type", "text/html; charset=UTF-8");
    // Generate the HTML document

    qDebug() << "HTTPSERVER : SEND MESSAGE FOR : " << sender;

    response.write("<html><body>\n");
    response.write(sender);
    response.write("</body></html>");

    sem.release(1);

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
