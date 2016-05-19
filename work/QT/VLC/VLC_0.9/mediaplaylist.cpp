#include "mediaplaylist.h"

MediaPlaylist * MediaPlaylist::playerList = NULL;

MediaPlaylist::MediaPlaylist(){}

MediaPlaylist* MediaPlaylist::getInstead(){
  if(MediaPlaylist::playerList == NULL){
      MediaPlaylist::playerList = new MediaPlaylist;
    }
  return MediaPlaylist::playerList;
}

