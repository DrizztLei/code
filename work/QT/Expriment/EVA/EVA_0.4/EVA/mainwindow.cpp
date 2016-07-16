#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  this -> setWindowIcon(QIcon(":/Image/FACE"));
  setWindowTitle(tr("EVA"));
  openAction = new QAction(QIcon(":/Image/FACE") , tr("Open") , this);
  openAction -> setShortcut(QKeySequence::Open);
  openAction -> setStatusTip("Open file");
  QObject:: connect(openAction , &QAction::triggered, this , &MainWindow::open);
  qDebug() << "I'm running here ." ;
  QMenu * file = menuBar() -> addMenu(tr("&File"));
  //file -> setStatusTip("File");
  file -> addAction(openAction);
  QToolBar * toolbar = addToolBar(tr("&File"));
  toolbar -> addAction(openAction);
  //this -> setBackingStore();
  //toolbar -> setStatusTip("Toolbar");
}

MainWindow::~MainWindow()
{
  openAction -> ~QAction();
  delete ui;
}
