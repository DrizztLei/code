#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUrl>
#include <QDebug>
#include <QObject>
#include <QFile>
#include <QPushButton>
#include <QMultimedia>
#include <QtMultimediaWidgets>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QListWidget>
#include <QString>
#include <QFileDialog>
#include <QSlider>
#include <QFileInfo>
#include <QWidget>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow

{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  virtual ~MainWindow();

private:
  int width , height , number;
  bool flag = true, pause = false;
  void init();
  void setScreenInfo();
  void setPause(bool mark);
  void setSize();
  void adjustPosition();
  void initPlayer();
  void setStatus(bool mark);
  void rename(QString title);
  void connect();
  void hideList();
  bool getStatus();
  bool isPause();
  void openFile();
  void setFile(QString filename);
  void addList(QFile file);
  int * getNumber();
  void setSlider(qint64 info);
  void save();
  void loadList();
  void dealFailed();
  void dealLoaded();

  QAction* getOpen();
  QAction* getClose();
  QAction* getExit();

  QUrl& getUrl();
  QPushButton* getMidle();
  QPushButton* getLeft();
  QPushButton* getRight();
  QListWidget* getList();
  QMediaPlayer* getPlayer();
  QString getFile();
  QSlider * getSlider();
  QMediaPlaylist * getMediaList();
  QLabel * getLabelLeft();
  QLabel * getLabelRight();

  QSlider * slider;
  Ui::MainWindow *ui;
  QString title;
  QMediaPlayer * player;
  QMediaPlaylist * playerlist;
  QVideoWidget * videoWidget;
  QString file;
  QUrl url;

};
#endif // MAINWINDOW_H
