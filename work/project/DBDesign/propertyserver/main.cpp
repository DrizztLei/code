
#include <QApplication>
#include <QDesktopWidget>
#include <QDir>
#include <string>
#include <QDebug>
#include <pthread.h>

#include "httpwindow.h"
#include <stdlib.h>
#include <unistd.h>

using namespace std;

/*
 * function head
 */

void* runAPP(void * args);


/*
 * function body
 */

void* runAPP(void * args)
{
    qDebug() << args;
    ((QApplication*)args)->exec();
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    /*
    pthread_t mession;
    qDebug() << &app ;
    int ret = pthread_create(&mession , NULL , &runAPP , (void*)&app);
    */
    HttpWindow http;

    //const QRect availableSize = QApplication::desktop()->availableGeometry(&httpWin);
    //httpWin.resize(availableSize.width() / 5, availableSize.height() / 5);
    //httpWin.move((availableSize.width() - httpWin.width()) / 2, (availableSize.height() - httpWin.height()) / 2);

    http.start();

    return app.exec();
}

