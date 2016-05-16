#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QTextEdit>
#include <QDebug>

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
  QTextEdit * edit;
  void closeEvent(QCloseEvent * event);
  bool setWindowModified(bool flag);

};

#endif // MAINWINDOW_H
