#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QDebug>
#include <QKeyEvent>
#include <QEvent>
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
  bool eventFilter(QObject *, QEvent *);
  QTextEdit * editor;
};

#endif // MAINWINDOW_H
