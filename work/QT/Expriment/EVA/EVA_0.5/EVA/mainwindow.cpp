#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{

  ui->setupUi(this);
  this -> setWindowTitle("VLC");
  this -> setWindowIcon(QIcon(":/Image/face"));
  //this -> setWindowPath(QString("~/work/"));

  open_action = new QAction(QIcon(":/Image/face") , tr("Open") , this);
  open_action -> setStatusTip("Open file in dialog");
  open_action -> setShortcut(QKeySequence::Open);
  //open_action -> setSeparator(QKeySequence::Open);

  save_action = new QAction(QIcon(":/Image/save") , tr("Save") , this);
  save_action -> setStatusTip("Save file");
  save_action -> setShortcut(QKeySequence::Save);

  play_action = new QAction(QIcon(":/Image/profile") , tr("Play") , this);
  play_action -> setSeparator("Play media");
  play_action -> setStatusTip("Set here to play media");

  //paly_action -> setShortcut(QKeySequence::p)
  //file_menu = new QMenuBar(this);

  file_menu = menuBar() -> addMenu(tr("File"));
  file_menu -> addAction(open_action);
  file_menu -> addAction(save_action);
  file_menu -> addAction(play_action);

  toolbar = addToolBar(tr("File"));
  toolbar -> addAction(open_action);
  toolbar -> addAction(save_action);
  toolbar -> addAction(play_action);

  text_edit = new QTextEdit(this);
  setCentralWidget(text_edit);

  connect(open_action , &QAction::triggered , this , &MainWindow::openFile);
  connect(save_action , &QAction::triggered , this , &MainWindow::saveFile);

  // The other is for qt4
  /*
    connect(open_action , SIGNAL(triggered()) , this , SLOT(openFile()));
    connect(save_action , SIGNAL(triggered()) , this , SLOT(saveFIle()));
  */

}

MainWindow::~MainWindow()
{

  open_action -> ~QAction();
  save_action -> ~QAction();
  play_action -> ~QAction();
  text_edit -> ~QTextEdit();

  delete ui;
}


void  MainWindow:: openFile(){
  qDebug() << "You are opening file.";
  QString path = QFileDialog::getOpenFileName(
        this ,
        "Selecting" ,
        tr("Open File"),
        tr("Text Files(*.txt")
        );
  if(!path.isEmpty()){
      QFile file(path);
      if(!file.open(QIODevice::ReadOnly | QIODevice :: Text)){
          //QMessageBox::warning(this , tr("Read File")), tr("Cannot open file :\n%1".arg(path));
          QMessageBox::warning(this ,
                                tr("Read File"),
                                tr("Cannot open file:\n%1").arg(path));
          return;
        }
      QTextStream in(&file);
      text_edit-> setText(in.readAll());
      file.close();
    }else{
      QMessageBox::warning(this , tr("Path") ,tr("You didn't choose any file"));
    }
}

void MainWindow:: saveFile(){
  qDebug() << "You are saving file.";
  QString path = QFileDialog::getSaveFileName(this ,
                                              tr("Save"),
                                              tr("."),
                                              tr("Text Files(*.txt) ;; PNG Files(*.png)"));

  if(!path.isEmpty()){
      QFile file(path);
       if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
          QMessageBox::warning(this , tr("Write File") , tr("Cannot open file:\n%1").arg(path));
          return;
        }

      QTextStream out(&file);
      out << text_edit -> toPlainText();
      file.close();

      /*
      QFileInfo qf(file);
      qDebug() << qf.size() << "\t For the size . " ;
      text_edit -> setText("");
      */

    }else{
      if(path.length() != 0){
        QMessageBox::warning(this , tr(".") , tr("Unable to write in file\n%1").arg(path));
      }
    }
}
