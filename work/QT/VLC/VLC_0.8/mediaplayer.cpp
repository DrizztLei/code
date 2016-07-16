#include "mediaplayer.h"

MediaPlayer * MediaPlayer::player = NULL;

MediaPlayer::MediaPlayer():QMediaPlayer(){}

MediaPlayer* MediaPlayer::getInstead(){
  if(MediaPlayer::player == NULL){
      MediaPlayer::player = new MediaPlayer;
    }
  return MediaPlayer::player;
}
