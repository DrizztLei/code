#ifndef MEDIAPLAYLIST_H
#define MEDIAPLAYLIST_H
#include <QMediaPlaylist>

class MediaPlaylist : public QMediaPlaylist
{
public:
  static  MediaPlaylist * getInstead();
private:
  MediaPlaylist();
  static MediaPlaylist * playerList;
};

#endif // MEDIAPLAYLIST_H
