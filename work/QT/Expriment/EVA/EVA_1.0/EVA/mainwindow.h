#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsWidget>
#include <QGraphicsLayout>
#include <QAbstractAnimation>
#include <QPixmap>

/*
namespace Ui {
  class MainWindow;
}
*/

class QGraphicsScene;
class QGraphicsView;
class GameController;


class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  virtual ~MainWindow();


  //Ui::MainWindow *ui;
private slots:
  void adjustViewSize();
private:
  void initScene();
  void initSceneBackground();

  QGraphicsScene * scene;
  QGraphicsView * view;

  GameController * game;

};


#endif // MAINWINDOW_H
