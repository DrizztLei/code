#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QObject>
#include <QString>
#include <QFileDialog>
#include <QtMultimediaWidgets>
#include <QVideoWidget>
#include <QLabel>
#include <QUrl>
#include "fileinfo.h"
#include "slider.h"
#include "file.h"
#include "pushbutton.h"
#include "mediaplayer.h"
#include "mediaplaylist.h"
#include "command.cpp"
#include "receiver.cpp"
#include "invoker.cpp"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow

{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  virtual ~MainWindow();

public:
  void setStatus(bool mark);
  bool getStatus();
  void openFile();
  void setFile(QString filename);
  void setSlider(qint64 info);
  void save();
  QAction* getOpen();
  QAction* getPre();
  QAction* getNext();
  QPushButton* getMidle();
  QPushButton* getLeft();
  QPushButton* getRight();
  QListWidget* getList();
  MediaPlayer* getPlayer();
  QString getFile();
  Slider * getSlider();
  MediaPlaylist * getMediaList();
  QLabel * getLabelLeft();
private:
  void init();
  void setScreenInfo();
  void setPause(bool mark);
  void setSize();
  void adjustPosition();
  void initPlayer();
  void rename(QString title);
  void connect();
  void hideList();
  bool isPause();
  void addList(File file);
  int * getNumber();
  void loadList();
  void dealFailed();
  void dealLoaded();
  QAction* getClose();
  QAction* getExit();
  QUrl& getUrl();
  QLabel * getLabelRight();
  Slider * slider;
  int width , height , number;
  bool flag = true, pause = false;
  Ui::MainWindow *ui;
  QString title;
  MediaPlayer * player;
  MediaPlaylist * playerlist;
  QVideoWidget * videoWidget;
  QString file;
  QUrl url;
  Receiver * receiver;
  Invoker * invoker;
};
#endif // MAINWINDOW_H
