#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUrl>
#include <QDebug>
#include <QObject>
#include <QFile>
#include <QIODevice>
#include <QPushButton>
#include <QMultimedia>
#include <QtMultimediaWidgets>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QListWidget>
#include <QDesktopWidget>
#include <QString>
#include <QDialog>
#include <QFileDialog>
#include <QVideoFrame>
#include <QSlider>

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
  int width , height;
  bool flag = true, pause = false;
  QSlider * slider;
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
//  void play();

  QAction* getOpen();
  QAction* getClose();
  QAction* getExit();

  //QOpenGLWidget* getOpengl();
  QUrl& getUrl();
  QPushButton* getMidle();
  QPushButton* getLeft();
  QPushButton* getRight();
  QListWidget* getList();
  QMediaPlayer* getPlayer();
  QString getFile();
  QSlider * getSlider();

  Ui::MainWindow *ui;
  QString title;
  QMediaPlayer * player;
  QMediaPlaylist * playerlist;
  QVideoWidget * videoWidget;
  QOpenGLWidget *openglWidget;
  QString file;
  QUrl url;
};
#endif // MAINWINDOW_H
