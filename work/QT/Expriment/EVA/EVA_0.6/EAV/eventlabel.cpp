#include <QLabel>
#include <QDebug>
#include <QString>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>

class EventLabel : public QLabel
{
protected:
  void mouseMoveEvent(QMouseEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
};

void EventLabel :: mouseMoveEvent(QMouseEvent *event){
  this -> setText(QString("<center><h1>Move :(%1 , %2) </h1></center>").arg(QString::number(event->x()) , QString :: number(event->y())));
}

void EventLabel :: mousePressEvent(QMouseEvent *event){
  this -> setText(QString("<center><h1>Press :(%1 , %2)</h1></center>").arg(QString::number(event->x()) , QString :: number(event->y())));
}

void EventLabel :: mouseReleaseEvent(QMouseEvent *event){
  //QString msg;
  //this -> setText(QString("<center><h1>Release :(%1 , %2)</h1></center>").arg(QString::number(event->x()) , QString :: number(event -> y())));
  this -> setText(QString("<center><h1>Release :(%1 , %2)</h1></center>").arg(QString::number(event->x()) , QString :: number(event->y())));
  qDebug() << ("<center><h1>Release :(%d , %d)</h1></center>", event->x() , event->y());
  //this -> setText(msg);
}
/*
int main(int argc , char ** argv){
  QApplication app(argc , argv);
  EventLabel * label = new EventLabel();
  label -> setWindowTitle("MouseEvent Demo");
  label -> resize(300,200);
  label -> show();
  app.exec();
  label -> ~EventLabel();
  return 0;
}
*/
