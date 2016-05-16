#include "mainwindow.h"
#include <QApplication>
#include <QTextEdit>
MainWindow :: MainWindow(QWidget * parent){

  text_editor = new QTextEdit(parent);
  setCentralWidget(text_editor);
  text_editor -> installEventFilter(this);
}

bool MainWindow :: eventFilter(QObject *obj, QEvent *event){
  if(obj == text_editor){
      if(event -> type() == QEvent :: KeyPress){
          QKeyEvent * keyEvent = static_cast<QKeyEvent *> (event);
          qDebug() << "Filting ." ;
          return true;
        }else{
          return false;
        }
    }else{
      return QMainWindow :: eventFilter(obj , event);
    }
}

MainWindow :: ~MainWindow(){
  text_editor -> ~QTextEdit();
}

int main(int argc , char ** argv){
  QApplication app(argc , argv);
  app.exec();
  return 0;
}
