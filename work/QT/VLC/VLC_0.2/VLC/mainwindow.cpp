#include "mainwindow.h"
//#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent)//,
  //ui(new Ui::MainWindow)
{
  /*
  init();
  connect();
  */
  qDebug() << "Error for unknow exceptiono ";
}
/*
void MainWindow::init(){
  title = "VLC";
  //ui->setupUi(this);
  hideList();  
  rename(title);
  setScreenInfo();
  adjustPosition();
  initPlayer();
  setSize();

  /*
  QVBoxLayout* mainLayout = new QVBoxLayout;
  mainLayout->addWidget(getList());
  mainLayout->addWidget(getMidle());
  mainLayout->addWidget(getLeft());
  mainLayout->addWidget(getRight());
  mainLayout->addWidget(getOpengl());
  setLayout(mainLayout);
  */

//}
/*
void MainWindow::setScreenInfo(){
  QDesktopWidget * desktop = QApplication::desktop();
  QRect screen = desktop -> screenGeometry();
  width = screen.width();
  height = screen.height();
}

void MainWindow::initPlayer(){
  player = new QMediaPlayer;
  playerlist = new QMediaPlaylist;
  videoWidget = new QVideoWidget(getOpengl());
  player->setMedia(url.fromLocalFile("/home/elvis/attack.wmv"));
}

void MainWindow::connect(){
  QObject::connect(getMidle(),&QPushButton::clicked,getPlayer(),[&](){
        if(getStatus()){
            //getOpengl()->hide();
            setStatus(false);
            getMidle()->setText("Stop");

            player->setVideoOutput(videoWidget);
            //player->setVideoOutput(getOpengl());

            QFile file("/home/elvis/Test.mp4");
            if(!file.open(QIODevice::ReadOnly)){
                qDebug() << "Error for resources busy or not found .";
                return ;
              }

            getPlayer()->setMedia(getUrl().fromLocalFile(file.fileName()));
            getPlayer()->play();
            videoWidget->resize(getOpengl()->width(),getOpengl()->height());
            videoWidget->show();
          }else{
            setStatus(true);
            getMidle()->setText("Play");
            getPlayer()->pause();
            //videoWidget->hide();
          }
      });
}

MainWindow::~MainWindow()
{
  delete playerlist;
  delete player;
 // delete ui;
}

void MainWindow::hideList(){
  getList()->hide();
}

QOpenGLWidget* MainWindow::getOpengl(){
  return ui->openGLWidget;
}


QListWidget *MainWindow::getList(){
  return ui->listWidget;
}

QPushButton* MainWindow::getMidle(){
  return ui->pushButton_1;
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
*/
