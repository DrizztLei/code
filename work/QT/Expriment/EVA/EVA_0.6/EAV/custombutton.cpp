#include "custombutton.h"
#include <QDebug>
#include <QApplication>
#include <QWidget>

CustomButton :: CustomButton(QWidget *parent) //: QPushButton(parent)
{
  connect (this , &CustomButton::clicked , this, &CustomButton::onButtonClicked);
}

void CustomButton :: onButtonClicked(){
  qDebug() << "You clicked the button ." ;
}

void CustomButton :: mousePressEvent(QMouseEvent *event){
  if(event -> button() == Qt::LeftButton){
      qDebug() << "Left" ;
    }else{
      QPushButton::mousePressEvent(event);
    }
}

bool CustomButton :: event(QEvent * e){
  if(e -> type() == QEvent::KeyPress){
      QKeyEvent * keyEvent = static_cast<QKeyEvent *>(e);
      if(keyEvent -> key() == Qt :: Key_Tab){
          qDebug() << "You clicke the TAB";
          return true;
        }
    }
  return QWidget::event(e);
}
/*

int main(int argc , char ** argv){
  QApplication app(argc , argv);
  CustomButton cb;
  cb.setText("This The Expriment .");
  cb.show();
  app.exec();
  return 0;
}
*/
