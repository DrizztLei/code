#include <QDebug>

#include "textformat.h"

TextFormat::TextFormat(QObject *parent) : QObject(parent)
{
    qDebug() << "INIT THE TEXTFORMAT CLASS .";
}

void TextFormat::dealText(const QString &placeholder, const QVariant &val, QSql::ParamType type)
{
    qDebug() << placeholder;
    qDebug() << val;
    qDebug() << type;
}

void TextFormat::dealText(const QVariant &val, QSql::ParamType type)
{
    qDebug() << val;
    qDebug() << type;
}
