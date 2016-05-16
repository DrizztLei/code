#include "mainwindow.h"
//#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  scene(new QGraphicsScene(this)),
  view (new QGraphicsView(scene , this)),
  //game(new GameController(*scene , this))
  //,ui(new Ui::MainWindow)

  //ui->setupUi(this);
  this -> setWindowTitle("EVA");
  setCentralWidget(view);
  resize(600,600);

  initScene();
  initSceneBackground();

  QTimer::singleShot(0,this,SLOT(adjustViewSize()));
}

MainWindow::~MainWindow()
{
  //delete ui;
}

void MainWindow::initScene(){
  scene -> setSceneRect(-100,-100,200,200);

}

void MainWindow::initSceneBackground(){
  QPixmap bg(TILE_SIZE , TILE_SIZEW);
  QPainter p(&bg);
  p.setBruch(QBrush(QT::gray));
  p.drawRect(0,0,TILE_SIZE,TILE_SIZE);
  view -> setBackgroundBrush(QBrush(bg));

}
