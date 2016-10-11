#ifndef SQL_H
#define SQL_H

#include <QSqlDatabase>
#include <QtSql>
#include <QObject>

class SQL : public QObject
{
    Q_OBJECT
public:

    explicit SQL(QObject *parent = 0);
    bool openDatabase(QString databaseName , QString IP = "127.0.0.1", QString databaseType = "QMYSQL");
    bool logIn(QString userName , QString userPasswd);

    QSqlDatabase* getDatabase();
    QSqlQuery* getQuery();

    virtual ~SQL();

signals:

public slots:

private:
    QSqlDatabase* db;
    QSqlQuery* query;
};

#endif // SQL_H
