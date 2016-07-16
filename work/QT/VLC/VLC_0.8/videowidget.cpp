#include "videowidget.h"

VideoWidget * VideoWidget::video = NULL;

//VideoWidget::VideoWidget(MainWindow *host):QVideoWidget(host){}

VideoWidget * VideoWidget::getInstead(MainWindow *host){
  if(VideoWidget::video == NULL){
      VideoWidget::video = new VideoWidget(host);
    }
  return VideoWidget::video;
}
