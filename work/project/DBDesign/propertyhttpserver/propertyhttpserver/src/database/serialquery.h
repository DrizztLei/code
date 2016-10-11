#ifndef SERIALQUERY_H
#define SERIALQUERY_H

#include <QDataStream>
#include <QSql>
#include <QSqlQuery>


class serialQuery: public QObject
{
    Q_OBJECT
public:
    explicit serialQuery(QObject *parent);
    serialQuery();
    virtual void serialize(QDataStream & dataStream);
    virtual void deSerialize(QDataStream & dataStream);
    virtual ~serialQuery();
    void setSQL(QString info);

    QSqlQuery* getSQL();

    QString getInfo();

    QString* string ;

    QSqlQuery* sql = Q_NULLPTR;

#ifndef QT_NO_DATASTREAM
    friend QDataStream& operator <<(QDataStream& dataStream , const serialQuery& object);
    friend QDataStream& operator >>(QDataStream& dataStream , serialQuery& object);
#endif
private:
    QString info;
signals:

public slots:
};

#endif // SERIALQUERY_H
