#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{

  ui->setupUi(this);
  edit = new QTextEdit(this);
  setCentralWidget(edit);
  connect(edit , &QTextEdit::textChanged , this , [=](){
      this -> setWindowModified(true);
    } );
  setWindowTitle("TextPad [*]");

}

MainWindow::~MainWindow()
{
  edit -> ~QTextEdit();
  delete ui;
}

bool MainWindow :: setWindowModified(bool flag){
  qDebug() << "Find the flag : " << flag ;
  return flag;
}

void MainWindow :: closeEvent(QCloseEvent * event){
  qDebug() << "Check for closeEvent" ;

}

/*
bool QObject :: event(QEvent *e){
  switch(e -> type()){
    case (QEvent :: Timer):
    timerEvent((QTimerEvent*) e);
    break;
    case (QEvent :: ChildAdded):
    case (QEvent :: ChildPolished):
    case (QEvent :: ChildRemoved):
          childEvent((QChildEvent*)e);
      break;
     default :
      if(e -> type() >= QEvent::User){
          customEvent(e);
          break;
        }
      return false;
  }
  return true;
}
*/
