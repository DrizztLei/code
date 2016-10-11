#include "mainwindow.h"
#include <QApplication>
#include <QSpinBox>
#include <QSlider>
#include <QObject>
#include <QHBoxLayout>

void (QSpinBox :: *spinBoxSignal)(int) = &QSpinBox::valueChanged;

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
//  MainWindow w;
//  w.show();
  QWidget window;
  window.setWindowTitle("EVA");
  window.setWindowIcon(QIcon("/home/elvis/Pictures/face.jpg"));
  QSpinBox * spinbox = new QSpinBox(&window);
  QSlider * slider = new QSlider(&window);
  spinbox -> setRange(0 , 1200);
  slider -> setRange(0 , 1200);
  QObject temp;
  temp.connect(slider , &QSlider::valueChanged,spinbox,&QSpinBox::setValue);
  temp.connect(spinbox , spinBoxSignal , slider , &QSlider::setValue);
  spinbox -> setValue(0);
  QHBoxLayout * layout = new QHBoxLayout();
  layout -> addWidget(slider);
  layout -> addWidget(spinbox);
  window.setLayout(layout);
  /*
  layout -> ~QLayout();
  spinbox -> ~QSpinBox();
  slider -> ~QSlider();
  */
  window.show();
  return a.exec();
}
