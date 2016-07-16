#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H
#include <QVideoWidget>
#include <mainwindow.h>

class MainWindow;

class VideoWidget : public QVideoWidget
{
public:
  static VideoWidget * getInstead(MainWindow* host);
private:
  VideoWidget(MainWindow* host):QVideoWidget(host){}
  static VideoWidget * video;
};

#endif // VIDEOWIDGET_H
