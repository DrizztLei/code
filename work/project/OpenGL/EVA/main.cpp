#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;

    w.move(768, 256);
    w.show();

    // w.initializeGL();

    w.resizeGL(512, 512);

    return a.exec();
}
