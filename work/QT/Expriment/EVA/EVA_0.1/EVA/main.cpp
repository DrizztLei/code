#include "mainwindow.h"
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QPushButton * button = new QPushButton("EVA");
  connect(button , &QPushButton::clicked,&QApplication::quit);
  button.show();
  /*
  MainWindow w;
  w.show();
  */
  return a.exec();
}
