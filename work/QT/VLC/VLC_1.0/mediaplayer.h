#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QMediaPlayer>

class MediaPlayer : public QMediaPlayer
{
public:
  static MediaPlayer * getInstead();
private:
  MediaPlayer();
  static  MediaPlayer * player;
};

#endif // MEDIAPLAYER_H
