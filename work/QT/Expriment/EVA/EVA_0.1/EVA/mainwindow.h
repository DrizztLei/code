#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QMainWindow>
#include <QWindow>
#include "ui_mainwindow.h"
#include <QtGui>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();


private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
