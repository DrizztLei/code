#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  this -> setWindowTitle(tr("Night"));
//  this -> setIconSize(QIcon(":/images/dock-picture"));
  window() -> setWindowIcon(QIcon(":/images/doc-picture"));
  openAction = new QAction(QIcon(":/images/doc-picture") , tr("&Open") , this);
  openAction -> setStatusTip(tr("Open an existing file"));
  connect(openAction , &QAction::triggered , this , &MainWindow::open);

  QMenu * file = menuBar() -> addMenu(tr("&File"));
  file -> addAction(openAction);

  QToolBar * toolBar = addToolBar(tr("&File"));
  toolBar -> addAction(openAction);
//  toolBar -> setStatusTip(tr("Unable to set tip here ?"));
//  QStatusBar * statusBar = statusBar();
//  statusBar -> addAction;
  QStatusBar * stateBar = statusBar();
  stateBar -> addAction(openAction);
}

MainWindow::~MainWindow()
{
  delete openAction;
  delete ui;
}

void MainWindow::open(){
  qDebug() << "I'm here " ;
  QMessageBox::information(this , tr("Information") , tr("Open here"));
}
