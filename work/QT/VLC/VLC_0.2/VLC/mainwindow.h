#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QUrl>
#include <QDebug>
#include <QObject>
#include <QFile>
#include <QIODevice>
#include <QPushButton>
#include <QMainWindow>
#include <QMultimedia>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QListWidget>
#include <QOpenGLWidget>
#include <QDesktopWidget>
/*
namespace Ui {
  class MainWindow;
}
*/
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  virtual ~MainWindow();

private:
  int width , height;
  bool flag = true;
  void init();
  void setScreenInfo();
  void setSize();
  void adjustPosition();
  void initPlayer();
  void setStatus(bool mark);
  void rename(QString title);
  void connect();
  void hideList();
  bool getStatus();
  QOpenGLWidget* getOpengl();
  QUrl& getUrl();

  QPushButton* getMidle();
  QPushButton* getLeft();
  QPushButton* getRight();
  QListWidget* getList();
  QMediaPlayer* getPlayer();

  //Ui::MainWindow *ui;
  QString title;
  QMediaPlayer * player;
  QMediaPlaylist * playerlist;
  QVideoWidget * videoWidget;
  QOpenGLWidget *openglWidget;
  QUrl url;

};
#endif // MAINWINDOW_H
