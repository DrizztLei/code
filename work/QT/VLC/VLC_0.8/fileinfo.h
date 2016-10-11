#ifndef FILEINFO_H
#define FILEINFO_H
#include <QFileInfo>
#include <QString>

class FileInfo : public QFileInfo
{
public:
  FileInfo():QFileInfo(){}
  FileInfo(QString path):QFileInfo(path){

  }
  static QString getName();
  static void setFile(QString file);
private:
  static FileInfo space;
};

#endif // FILEINFO_H
