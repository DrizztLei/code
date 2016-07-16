#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include "newspaper.h"
#include "reader.h"
#include <QObject>

/*
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QPushButton button("EVA");
  QObject :: connect(&button, &QPushButton::clicked , &QApplication::quit);
  button.show();
  //MainWindow w;
  //w.show();

  return a.exec();
}
*/

/*
int main(int argc , char ** argv){
  QApplication app(argc , argv);
  QPushButton button("Quit");
  QObject::connect(&button,&QPushButton::clicked,[](bool){
      qDebug() << "You clicked me";
    });
  button.show();
  return app.exec();
}
*/
/*
int main(int argc , char ** argv){
  QCoreApplication app(argc , argv);
  Newspaper newspaper("Newspaper A");
  Reader reader;
  QObject :: connect(&newspaper , &Newspaper::newPaper , &reader , &Reader::receiveNewspaper);
  newspaper.send();
  return app.exec();
}
*/

int main(int argc , char ** argv){
  //qDebug() << "argc : "  << argc << "\t argv : " << argv <<"\n";
  return 0;
}
