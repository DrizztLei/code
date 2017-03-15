#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <iostream>

class GLWidget;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();
    int saveImg(std::string filename, int width, int height);

private slots:
    void setCurrentGlWidget();
    void rotateOneStep();
    void capture(QMouseEvent *event);

private:
    enum { NumRows = 1, NumColumns = 1 };
    GLWidget *glWidgets[NumRows][NumColumns];
    GLWidget *currentGlWidget;
};

#endif
