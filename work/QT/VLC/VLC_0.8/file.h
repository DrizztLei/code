#ifndef FILE_H
#define FILE_H
#include <QFile>
#include <QString>

class File : public QFile
{
public:
  static File * getFile(bool flag = true);
  File():QFile(){

  }
  File(QString path):QFile(path){

  }
private:
  static const File * his ;
  static const QString filename;
};

#endif // FILE_H
