#ifndef HTTPSERVER_H
#define HTTPSERVER_H
#include <QCoreApplication>
#include <QDataStream>
#include <QString>
#include <qsemaphore.h>
#include <QSqlQuery>

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"
#include "../src/database/sql.h"


class HttpServer : public HttpRequestHandler
{
public:
    explicit HttpServer();
    explicit HttpServer(QCoreApplication* app);

    void service(HttpRequest& request , HttpResponse& response);
    void setDatabase(QSqlDatabase* db);
    void setSQL(SQL* point);

    QSqlDatabase* getDatabase();
    SQL* getSQL();
    // QSqlQuery& operator =(const QSqlQuery& other);

    virtual ~HttpServer();
private:
    QSqlDatabase* db;
    SQL* sql;
    QSemaphore sem;
};

#endif // HTTPSERVER_H
