#include <QApplication>
#include <QObject>
#include <QWindow>
#include <QLabel>
#include <QWidget>
#include <QEvent>
#include <QDebug>
#include <QtEvents>

class Label : public QWidget
{
public:
  Label(){
//    insallEventFilter(this);
    installEventFilter(this);
  }
  bool eventFilter(QObject * watched, QEvent * event){
    if(watched == this){
        if(event -> type() == QEvent :: MouseButtonPress){
            qDebug() << "Event Filter";
          }
      }
    return false;
  }

protected:
  bool event(QEvent *e){
    if(e -> type() == QEvent :: MouseButtonPress){
        qDebug() << "Event for event function" ;
      }
      return QWidget::event(e);
  }

private:
};

class EventFilter : public QObject{
public:
  EventFilter(QObject * watched , QObject * parent = 0): QObject(parent),
    m_watched(watched){

  }
  bool eventFilter(QObject *wathed, QEvent *event){
  if(wathed == m_watched){
      if(event -> type() == QEvent :: MouseButtonPress){
          qDebug() << "QApplication :: eventFilter";
        }
    }
  return false;
}

private:
  QObject * m_watched;
};


int main(int argc , char ** argv){
  QApplication app(argc , argv);
  Label label;
  app.installEventFilter(new EventFilter(&label , &label));
  label.show();
  int result = app.exec();
  return result;
}
