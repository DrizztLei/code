#include "fileinfo.h"

FileInfo FileInfo::space = FileInfo(QString(""));

QString FileInfo::getName(){
  return FileInfo::space.fileName();
}

void FileInfo::setFile(QString file){
  FileInfo::space = FileInfo(file);
}
