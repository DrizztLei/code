#ifndef LABEL_H
#define LABEL_H
#include <QLabel>
#include <ui_mainwindow.h>

namespace Ui {
  class MainWindow;
}

enum LABEL{
   LEFT,
   RIGHT
};

class Label : public QLabel
{
public:
  Label():QLabel(){

  }
  static void get(LABEL flag);
private:

};

#endif // LABEL_H
