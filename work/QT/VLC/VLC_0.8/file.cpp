#include "file.h"

const QString File::filename = "./his.m3u";
const File* File::his = new File(File::filename);

File * File::getFile(bool flag){
  if(flag){
     return File::his;
    }
  else return new File();
}
