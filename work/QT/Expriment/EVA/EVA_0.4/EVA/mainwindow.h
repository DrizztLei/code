#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QDebug>
#include <QDialog>
namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  QAction * openAction;
  void open(){
    qDebug() << "I'm opening . ";
    //QDialog dialog(this);
    QDialog * dialog = new QDialog(this);
    dialog -> setWindowTitle(tr("Info from EVA"));
    dialog -> setWindowIcon(QIcon(":/Image/FACE"));
    //dialog.exec();
    dialog -> show();
    connect(dialog
            , &QDialog :: finished
            , this
            , &MainWindow :: free);
    dialog -> setAttribute(Qt::WA_DeleteOnClose);

    /*
    QObject :: connect(&newspaper ,
                       (void (Newspaper ::*)(const QString & , const QDat &)),
                       &reader,
                       &Reader::reaceiveNewspaper
                       );
    */

  }
  void free(){
//    dialog -> ~QDialog();
    qDebug() << "I wanna delete it here .... But failed ." ;

  }
};

#endif // MAINWINDOW_H
