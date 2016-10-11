#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  this -> setWindowTitle("EVA");
  editor = new QTextEdit(this);
  editor -> installEventFilter(this);
//  this -> installEventFilter(editor);

}

MainWindow::~MainWindow()
{
  delete editor;
  delete ui;
}


bool MainWindow::eventFilter(QObject * obj, QEvent *event){
  if(obj == editor){
      if(event -> type() == QEvent :: KeyPress){
          QKeyEvent * key_event = static_cast<QKeyEvent*>(event);
          qDebug() << "You filter the key_event : " << char(key_event -> key());
          return true;
        }
       return false;
    }else{
      return QMainWindow::eventFilter(obj,event);
    }

}

