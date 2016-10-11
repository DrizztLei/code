#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QAction>
#include <QToolBar>
#include <QTextEdit>
#include <QFileDialog>
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
  QAction * open_action , * save_action , * play_action;
  QMenu * file_menu ;
  QToolBar * toolbar;
  QTextEdit * text_edit;
  void openFile();
  void saveFile();
};
#endif // MAINWINDOW_H
