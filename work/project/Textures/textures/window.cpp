#include <QtWidgets>

#include "glwidget.h"
#include "window.h"
#include <QDebug>

Window::Window()
{
    QGridLayout *mainLayout = new QGridLayout;

    for (int i = 0; i < NumRows; ++i)
    {
        for (int j = 0; j < NumColumns; ++j)
        {
            QColor clearColor;

            clearColor.setHsv(((i * NumColumns) + j) * 255 / (NumRows * NumColumns - 1), 255, 63);

            glWidgets[i][j] = new GLWidget;
            glWidgets[i][j]->setClearColor(clearColor);
            glWidgets[i][j]->rotateBy(+42 * 16, +42 * 16, -21 * 16);

            mainLayout->addWidget(glWidgets[i][j], i, j);

            connect(glWidgets[i][j], &GLWidget::clicked, this, &Window::setCurrentGlWidget);
        }
    }

    setLayout(mainLayout);

    currentGlWidget = glWidgets[0][0];

    /*
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(rotateOneStep()));
    timer->start(20);
    */

    setWindowTitle(tr("Textures"));
    move(768, 256);
    resize(512, 512);

    connect(currentGlWidget, &GLWidget::clicked, currentGlWidget, &GLWidget::capturePicture);
}

void Window::setCurrentGlWidget()
{
    currentGlWidget = qobject_cast<GLWidget *>(sender());
}

void Window::rotateOneStep()
{
    if (currentGlWidget)
    {
        currentGlWidget->rotateBy(+2 * 16, +2 * 16, -1 * 16);
    }
}

int Window::saveImg(std::string filename, int height, int width)
{
    // glWidgets[0][0]->saveImg(filename, height, width);

    int residual = 4;
    int residual_four_height = height % residual;
    int residual_four_width = width % residual;

    if (residual_four_height != 0)
    {
        height += residual - residual_four_height;
    }

    if (residual_four_width != 0)
    {
        width += residual - residual_four_width;
    }

    qDebug() << "RESIED HEIGHT : " << height;
    qDebug() << "RESIED WIDTH : " << width;
    qDebug() << "SAVED IMG : " << QString::fromStdString(filename);

    glWidgets[0][0]->test(filename, height, width);

    // glWidgets[0][0]->saveWithCV(filename, height, width);
    // glWidgets[0][0]->test(filename, height, width);
    return 0;
}

void Window::capture(QMouseEvent *event)
{

    qDebug() << "RUN WINDOWS CAPTURE";
    currentGlWidget->capturePicture();

}
