#ifndef TEXTFORMAT_H
#define TEXTFORMAT_H

#include <QObject>
#include <QVariant>
#include <QSql>
#include <QDebug>

class TextFormat : public QObject
{
    Q_OBJECT
public:
    explicit TextFormat(QObject *parent = 0);

signals:

public slots:
    static void dealText(const QString& placeholder , const QVariant& val , QSql::ParamType type = QSql::In);
    static void dealText(const QVariant& val , QSql::ParamType type = QSql::In);
};

#endif // TEXTFORMAT_H
