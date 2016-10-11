#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWindow>
#include <QEvent>
#include <QTextEdit>
#include <QMainWindow>
#include <QDebug>
#include <QtEvents>
#include <QWidget>
namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
protected:
  bool eventFilter(QObject * obj , QEvent * event);
private:
  Ui::MainWindow *ui;
  QTextEdit* text_editor;
};

#endif // MAINWINDOW_H
