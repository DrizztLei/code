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
  title = "VLC";
  ui->setupUi(this);
  setFile("/home/elvis/Music/BilibiliJJ.COM-aLIEzmzkver.抒情版xALIEZ点进来你会收藏的_(Av2285257,P1).mp4");
  rename(title);
  setScreenInfo();
  adjustPosition();
  initPlayer();
  setSize();
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
  videoWidget->move(0,45);
  videoWidget->resize(730,450);
  slider = new QSlider();
  player->setVideoOutput(videoWidget);
  player->setMedia(getUrl().fromLocalFile(getFile()));
  videoWidget->show();
}

void MainWindow::connect(){

  QObject::connect(getMidle(),&QPushButton::clicked,getPlayer(),[&](){
        if(getStatus()){
            qDebug() << "Function call for now 1....";
            QFile file(getFile());
            if(!file.open(QIODevice::ReadOnly)){
                qDebug() << "Error for resources busy or not found .";
                return ;
              }
            setStatus(false);
            getMidle()->setText("pause");

            getPlayer()->play();

            //getSlider()->setMaximum();
          }else{
            setStatus(true);
            qDebug() << "Function call for now 2....";
            getMidle()->setText("play");
            getPlayer()->pause();
          }
      });

  QObject::connect(getOpen() , &QAction::triggered, [&](){
      openFile();
    });

  QObject::connect(getList() , &QListWidget::itemClicked, [&](QListWidgetItem * item){
      QString filename = item->text();
      setFile(filename);
      getPlayer()->setMedia(getUrl().fromLocalFile(getFile()));
      qDebug() << "File name for : " << filename ;
      setStatus(true);
      emit getMidle()->click();
  });

  QObject::connect(getPlayer(), &QMediaPlayer::positionChanged,getSlider(),[&](qint64 info){
    qDebug() << info;
    getSlider()->setValue(info);
  });
  QObject::connect(getSlider() ,&QSlider::valueChanged,getPlayer(),&QMediaPlayer::setPosi);
}

void MainWindow::openFile(){
    QString filename = QFileDialog::getOpenFileName(this, tr("VLC player"), " ",  tr("Allfile(*.*);;mp3file(*.mp3)"));
    if(filename.length() != 0){
          qDebug() << getFile();
          qDebug() << filename;
          setFile(filename);
          getList()->addItem(getFile());
          setStatus(true);
          getPlayer()->setMedia(getUrl().fromLocalFile(getFile()));
          emit getMidle()->click();
      }else{
           qDebug() << "Error for unchoose file.";
      }
}

MainWindow::~MainWindow()
{
  delete playerlist;
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
