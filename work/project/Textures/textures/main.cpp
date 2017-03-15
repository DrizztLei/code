#include <QApplication>
#include <QSurfaceFormat>
#include <window.h>

#include <QDebug>
#include <GL/glut.h>

int main(int argc, char *argv[])
{
    /*
    std::string filename = "test_img.png";
    int width = 1920;
    int height = 1080;
    */

    Q_INIT_RESOURCE(textures);

    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    Window window;

    window.show();

    return app.exec();
}
