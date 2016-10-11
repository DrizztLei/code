#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "commandset.cpp"
#include "command.cpp"
#include "receiver.cpp"
#include "invoker.cpp"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  init();
  connect();
}

void MainWindow::init(){
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
  player = MediaPlayer::getInstead();
  playerlist = MediaPlaylist::getInstead();
  videoWidget = new QVideoWidget(this);
  videoWidget->move(0,45);
  videoWidget->resize(730,450);
  player->setVideoOutput(videoWidget);
  player->setPlaylist(playerlist);
  videoWidget->show();
}

void MainWindow::connect(){
  receiver = new Receiver();
  invoker = new Invoker();

  Command * play_music = new play(receiver , this);
  Command * play_pre = new music_pre(receiver , this);
  Command * play_next = new music_next(receiver , this);
  Command * open = new file_open(receiver , this);

  /*
  Command * list_choose = new list_op(receiver , this);
  Command player_to_slider = new p_to_s(receiver , this);
  Command slider_to_player = new s_to_p(receiver , this);
  */

  invoker->setCommand(play_music);
  invoker->setCommand(play_pre);
  invoker->setCommand(play_next);
  invoker->setCommand(open);
  invoker->runCommand();

  QObject::connect(getList() , &QListWidget::itemClicked, [&](QListWidgetItem * item){
      QString filename = item->text();
      setFile(filename);
      FileInfo::setFile(getFile());
      for(int i = 0 ; i < getList()->count();i++){
          if(getMediaList()->media(i).canonicalUrl().fileName().compare(FileInfo::getName()) == 0){
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
    int min , sec , video;
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
    getLabelLeft()->setText( summary );
    video = getPlayer()->position();
    int value = getSlider()->value()-(video);
    value = value > 0 ? value : -value;
    if(value > 1){
      getPlayer()->setPosition(info);
    }
  });

//  Command player_to_main = new p_to_m(receiver , this);
  QObject::connect(getPlayer() ,&QMediaPlayer::durationChanged, this , &MainWindow::setSlider);

//  Command main_to_main = new m_to_m(receiver , this);
  QObject::connect(this , &MainWindow::destroyed , this , &MainWindow::save);

//  Command action_pre = new action_music_pre(receiver , this);
  QObject::connect(ui->actionPrevious , &QAction::triggered , getLeft() , &QPushButton::click);

//  Command action_next = new action_next(receiver , this);
  QObject::connect(ui->actionNext , &QAction::triggered , getRight() , &QPushButton::click);

}

void MainWindow::openFile(){
    QString filename = QFileDialog::getOpenFileName(this, tr("VLC player"), "/home/elvis/Music/",  tr("Allfile(*.*);;mp3file(*.mp3)"));
    if(filename.length() != 0){
          qDebug() << "Get file for : " << filename;
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

MediaPlayer * MainWindow::getPlayer(){
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

Slider* MainWindow::getSlider(){
  //return (<static_cast>Slider*(ui->horizontalSlider));
  return (Slider*)(ui->horizontalSlider);
}

void MainWindow::addList(File file){
  getMediaList()->addMedia(getUrl().fromLocalFile(file.fileName()));
}

MediaPlaylist *MainWindow::getMediaList(){
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
  //QFile * file = new QFile("./his.m3u");
  File * file = File::getFile();
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
}

QLabel * MainWindow::getLabelRight(){
  return ui->label;
}

QLabel * MainWindow::getLabelLeft(){
  return ui->label_2;
}

void MainWindow::loadList(){
  File * file = File::getFile();
  file->open(QIODevice::ReadOnly);
  getMediaList()->load(file , "m3u");
  file->close();
  for(int i = 0 ; i < getMediaList()->mediaCount() ; i++){
      QString name = getMediaList()->media(i).canonicalUrl().fileName();
      getList()->addItem(File(name).fileName());
    }
}

void MainWindow::dealFailed(){
  qDebug() << "Load the file failed." ;
}

void MainWindow::dealLoaded(){
  qDebug() << "Load the file succeeded.";
}
