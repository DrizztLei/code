#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  init();
  connect();
}

void MainWindow::init(){
  ui->label = new QLabel();
  ui->label_2 = new QLabel();
  title = "VLC";
  ui->setupUi(this);
  rename(title);
  setScreenInfo();
  adjustPosition();
  initPlayer();
  setSize();
  loadList();
}

void MainWindow::setScreenInfo(){
  QDesktopWidget * desktop = QApplication::desktop();
  QRect screen = desktop -> screenGeometry();
  width = screen.width();
  height = screen.height();
}

void MainWindow::initPlayer(){
  player = new QMediaPlayer;
  playerlist = new QMediaPlaylist;
  videoWidget = new QVideoWidget(this);
  slider = new QSlider();
  videoWidget->move(0,45);
  videoWidget->resize(730,450);
  player->setVideoOutput(videoWidget);
  player->setPlaylist(playerlist);
  videoWidget->show();
}

void MainWindow::connect(){
  QObject::connect(getMidle(),&QPushButton::clicked,getPlayer(),[&](){
        if(getStatus()){
            setStatus(false);
            getMidle()->setText("pause");
            getPlayer()->play();
          }else{
            setStatus(true);
            getMidle()->setText("play");
            getPlayer()->pause();
          }
      });

  QObject::connect(getLeft(),&QPushButton::clicked,getPlayer(),[&](){
      getMediaList()->setCurrentIndex(getMediaList()->previousIndex());
      getPlayer()->play();
    });

  QObject::connect(getRight(),&QPushButton::clicked,getPlayer(),[&](){
      getMediaList()->setCurrentIndex(getMediaList()->nextIndex());
      getPlayer()->play();
    });

  QObject::connect(getOpen() , &QAction::triggered, [&](){
      openFile();
    });

  QObject::connect(getList() , &QListWidget::itemClicked, [&](QListWidgetItem * item){
      QString filename = item->text();
      setFile(filename);
      QFileInfo fi = QFileInfo(getFile());
      for(int i = 0 ; i < getList()->count();i++){
          if(getMediaList()->media(i).canonicalUrl().fileName().compare(fi.fileName()) == 0){
              getMediaList()->setCurrentIndex(i);
            }
        }
      setStatus(true);
      emit getMidle()->click();
  });

  QObject::connect(getPlayer(), &QMediaPlayer::positionChanged,getSlider(),[&](qint64 info){
    getSlider()->setValue(info);
  });

  QObject::connect(getSlider() ,&QSlider::valueChanged,getPlayer(),[&](qint64 info){
    getPlayer()->setPosition(info);
    int min , sec;
    sec = info / 1000;
    min = sec / 60;
    sec = sec % 60;
    QString str_min = QString();
    str_min.setNum(min);
    if(min < 10) str_min = "0" + str_min;
    QString str_sec = QString();
    str_sec.setNum(sec);
    if(sec < 10) str_sec = "0" + str_sec;
    QString summary = str_min + ":" + str_sec;
    //qDebug() << "Get the info : " << summary;
    getLabelLeft()->setText(
          summary
          );
  });

  QObject::connect(getPlayer() ,&QMediaPlayer::durationChanged,this , &MainWindow::setSlider);

  QObject::connect(this , &MainWindow::destroyed , this , &MainWindow::save);

}

void MainWindow::openFile(){
    QString filename = QFileDialog::getOpenFileName(this, tr("VLC player"), "/home/elvis/Music/",  tr("Allfile(*.*);;mp3file(*.mp3)"));
    if(filename.length() != 0){
          qDebug() << filename;
          setFile(filename);
          QFileInfo fi = QFileInfo(getFile());
          for(int i = 0 ; i < getList()->count();i++){
              qDebug() << getList()->item(i)->text();
                  if(getList()->item(i)->text().compare(fi.fileName()) == 0){
                      getMediaList()->setCurrentIndex(i);
                      setStatus(true);
                      emit getMidle()->click();
                      return ;
                    }
            }
          getList()->addItem(fi.fileName());
          setStatus(true);
          getMediaList()->addMedia(getUrl().fromLocalFile(getFile()));
          getMediaList()->setCurrentIndex(getMediaList()->mediaCount()-1);
          emit getMidle()->click();
      }else{
           qDebug() << "Error for unchoose file.";
      }
}

MainWindow::~MainWindow()
{
  delete player;
  delete ui;
}

void MainWindow::hideList(){
  getList()->hide();
}

QListWidget *MainWindow::getList(){
  return ui->listWidget;
}

QPushButton* MainWindow::getMidle(){
  return ui->pushButton;
}

QPushButton* MainWindow::getLeft(){
  return ui->pushButton_2;
}

QPushButton* MainWindow::getRight(){
  return ui->pushButton_3;
}

void MainWindow::setSize(){
  setFixedSize(0.5 * width , 0.618 * 0.5 * width);
}

void MainWindow::adjustPosition(){
  move(width/4 , height/2 - 0.618 * 0.5 * width * 0.5);
}

QMediaPlayer * MainWindow::getPlayer(){
  return player;
}

QUrl& MainWindow::getUrl(){
  return url;
}

bool MainWindow::getStatus(){
  return flag;
}

void MainWindow::setStatus(bool mark){
  flag = mark;
}

void MainWindow::rename(QString title){
  this->setWindowTitle(title);
}

void MainWindow::setPause(bool mark){
  pause = mark;
}

bool MainWindow::isPause(){
  return pause;
}

QAction* MainWindow::getOpen(){
  return ui->actionOpen;
}

QAction* MainWindow::getClose(){
  return ui->actionClose;
}

QAction* MainWindow::getExit(){
  return ui->actionExit;
}

void MainWindow::setFile(QString filename){
  file = filename;
}

QString MainWindow::getFile(){
  return file;
}

QSlider* MainWindow::getSlider(){
  return ui->horizontalSlider;
}

void MainWindow::addList(QFile file){
  getMediaList()->addMedia(getUrl().fromLocalFile(file.fileName()));
}

QMediaPlaylist *MainWindow::getMediaList(){
  return playerlist;
}

int * MainWindow::getNumber(){
  return &number;
}

void MainWindow::setSlider(qint64 info){
  getSlider()->setMinimum(0);
  getSlider()->setMaximum(info);
  int min , sec;
  sec = info / 1000;
  min = sec / 60;
  sec = sec % 60;
  QString str_min = QString();
  str_min.setNum(min);
  if(min < 10) str_min = "0" + str_min;
  QString str_sec = QString();
  if(sec < 10) str_min = "0" + str_min;
  str_sec.setNum(sec);
  getLabelRight()->setText(str_min+":"+str_sec);
}

void MainWindow::save(){
  QFile * file = new QFile("./his.m3u");
  if(file->exists()){
      qDebug() << "File exists" ;
    }else{
      qDebug() << "File not exists";
      file->open(QIODevice::WriteOnly);
      file->close();
    }
  file->open(QIODevice::WriteOnly);
  if(file->isWritable()){
      qDebug() << "file can be overwrite";
    }else{
      qDebug() << "file can't be overwrite";
    }
  bool flag = getMediaList()->save(file,"m3u");
  file->close();
  if(flag) {
      //qDebug() << "We should save it.";
  }else{
      qDebug() << "Error for not save the status.";
    }
  delete getMediaList();
  delete file;
}

QLabel * MainWindow::getLabelRight(){
  return ui->label;
}

QLabel * MainWindow::getLabelLeft(){
  return ui->label_2;
}

void MainWindow::loadList(){

  QFile file("./his.m3u");
  file.open(QIODevice::ReadOnly);
  getMediaList()->load(&file , "m3u");
  file.close();
  for(int i = 0 ; i < getMediaList()->mediaCount() ; i++){
      QString name = getMediaList()->media(i).canonicalUrl().fileName();
      //qDebug() << "Get the media list for : "  << name;
      getList()->addItem(QFile(name).fileName());
    }
}

void MainWindow::dealFailed(){
  qDebug() << "Load the file failed." ;
}

void MainWindow::dealLoaded(){
  qDebug() << "Load the file succeeded.";
}
