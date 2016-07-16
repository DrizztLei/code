#ifndef URL_H
#define URL_H
#include <QUrl>
#include <QString>

class Url : public QUrl
{
public:
  Url * getInstead(QString path);
  Url * setInstead(QString path);
private:
  Url(QString path):Qurl(path){}
  //static Url * url;
};

#endif // URL_H
