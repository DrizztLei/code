#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui -> setupUi(this);
  this -> setWindowTitle(tr("EVA"));
  this -> setWindowIcon(QIcon(":/images/MARK"));
}

MainWindow::~MainWindow()
{
  delete ui;
}
