#include "widget.h"
#include "ui_widget.h"

#include <math.h>

#include <QKeyEvent>
#include <QDebug>
#include <QMouseEvent>
#include <QColorDialog>
#include <GL/glu.h>
#include <QtOpenGL/QGL>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>

#include <opencv2/opencv.hpp>


Widget::Widget(QWidget *parent):QOpenGLWidget(parent)
{
    qDebug() << "widget init.";

    setFormat(QSurfaceFormat());

    // rotationX = -21.0;
    // rotationY = -57.0;

    rotationX = 0;
    rotationY = 0;
    rotationZ = 0;

    faceColors[0] = Qt::red;
    faceColors[1] = Qt::green;
    faceColors[2] = Qt::blue;
    faceColors[3] = Qt::yellow;

    translateX = 0;
    translateY = 0;
    translateZ = -10;

    scaledX = 1;
    scaledY = 1;
    scaledZ = 1;

    rotateAngle = 0;

    rotateX = 0;
    rotateY = 0;
    rotateZ = 0;

    depth_near = 6;
    depth_far = 14;
}

Widget::~Widget()
{

}

void Widget::initializeGL()
{

    // qglClearColor(Qt::black);
    // glClearColor();

    setGeometry(768, 256, 512, 512); // set the position and size

    glShadeModel(GL_FLAT);// set the shade smooth type
    glClearDepth(1.0);// set the depth
    glEnable(GL_DEPTH_TEST);// enable depth test
    glEnable(GL_CULL_FACE);// enable cull face

    glDepthFunc(GL_LEQUAL);// set depth test type

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);// check perspective check

}

void Widget::resizeGL(int width, int height)
{
    // qDebug() << "resize opengl.";

    glViewport(0, 0, width,height);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glFrustum(-2.3, 2.3, -4, 4, depth_near, depth_far);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
    if (event->buttons() & Qt::LeftButton)
    {
        qDebug() << "Press left botton . no thing happened.";
    }
    else if (event->buttons() & Qt::RightButton)
    {
        QPoint position = event->pos();
        int win_x = position.x();
        int win_y = position.y();
        qDebug() << "POSITION : " << position;
        capture(win_x, win_y, win_x + 100, win_y + 100);
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{

    GLfloat dx = GLfloat(event->x() - lastPos.x()) / width();
    GLfloat dy = GLfloat(event->y() - lastPos.y()) / height();

    if(event->buttons() & Qt::LeftButton)
    {
        rotationX -= 180 * dy;
        rotationY -= 180 * dx;
        update();
    }
    else if(event->buttons() & Qt::RightButton)
    {
        rotationX -= 180 * dy;
        rotationZ -= 180 * dx;
        update();
    }
    lastPos = event->pos();
}

void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{

    int face = faceAtPosition(event->pos());
    if(face != -1)
    {
        QColor color = QColorDialog::getColor(faceColors[face], this);
        if(color.isValid())
        {
            qDebug() << color;
            faceColors[face] = color;
            paintGL();
        }
    }
}

int Widget::faceAtPosition(const QPoint &pos)
{
    qDebug() << "face at position : " << pos;

    const int MaxSize = 512;
    GLuint buffer[MaxSize];
    GLint viewport[4];
    makeCurrent();
    glGetIntegerv(GL_VIEWPORT, viewport);
    glSelectBuffer(MaxSize, buffer);
    glRenderMode(GL_SELECT);

    glInitNames();
    glPushName(0);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    // gluPickMatrix(GLdouble(pos.x()), GLdouble(viewport[3] - pos.y()), 5.0, 5.0, viewport);

    GLfloat x = GLfloat(width()) / height();
    glFrustum(-x, x, -1.0, 1.0, 4.0, 15.0);
    draw();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    if(!glRenderMode(GL_RENDER))
    {
       return -1;
    }

    return buffer[3];
}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw();
}

void Widget::draw()
{
    static const GLfloat P1[3] = {0.0, 0, +2.0}; // point c
    static const GLfloat P2[3] = {4, 0, -1.0}; // point a
    static const GLfloat P3[3] = {-4, 0, -1.0}; // point b
    static const GLfloat P4[3] = {0.0, 3.0, 0.0}; // point d

    static const GLfloat *const coords[4][3] =
    {
        {P1, P2, P3}, {P1, P3, P4}, {P1, P4, P2}, {P2, P4, P3}
    };

    glMatrixMode(GL_MODELVIEW); // set the projection matrix
    glLoadIdentity(); // reset the projection matrix

    glTranslated(translateX, translateY, translateZ);
    glScaled(scaledX, scaledY, scaledZ);
    // glRotatef(rotateAngle, rotateX, rotateY, rotateZ);

    glDepthRange(0, 1);
    glClear(GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_ALWAYS);

    glRotatef(rotationX, 1.0, 0.0, 0.0);
    glRotatef(rotationY, 0.0, 1.0, 0.0);
    glRotatef(rotationZ, 0.0, 0.0, 1.0);

    for(int i = 0; i < 4; ++i)
    {
        glLoadName(i);

        glBegin(GL_TRIANGLES);

        GLfloat alpha = faceColors[i].alphaF();
        GLfloat red = faceColors[i].redF();
        GLfloat green = faceColors[i].greenF();
        GLfloat blue = faceColors[i].blueF();

        glColor4f(red, green, blue, alpha);

        for(int j = 0; j < 3; ++j)
        {
            glVertex3f(coords[i][j][0], coords[i][j][1], coords[i][j][2]);
        }
        glEnd();
    }

    /*
    glColor3ub(0, 255, 0);

    glBegin(GL_LINE_LOOP);

    glVertex3f(0, 0, 1.5);
    glVertex3f(0, 4, 1.5);
    glVertex3f(4, 4, 1.5);
    glVertex3f(4, 0, 1.5);

    glEnd();
    glFlush();
    */
}

void Widget::capture(int start_x , int start_y, int end_x, int end_y)
{

    this->start_x = start_x;
    this->start_y = start_y;
    this->end_x = end_x;
    this->end_y = end_y;

    int distance_x = end_x - start_x;
    int distance_y = end_y - start_y;

    /*

    int window_width = width();
    int window_height = height();

    resizeGL(window_width, window_height);
    paintGL();
    update();

    */

    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;

    glGetIntegerv(GL_VIEWPORT, viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);

    winZ = 0;

    winX = (float)start_x;
    winY = viewport[3] - (float)start_y;

    glReadPixels(start_x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

    // qDebug() << winZ;

    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &near_a_x, &near_a_y, &near_a_z);
    // qDebug() << "near_a_x : " << near_a_x << "\tnear_a_y : " << near_a_y << "\tnear_a_z : " << near_a_z;

    winX = (float)(start_x + distance_x);
    winY = viewport[3] - (float)start_y;

    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &near_b_x, &near_b_y, &near_b_z);
    // qDebug() << "near_b_x : " << near_b_x << "\tnear_b_y : " << near_b_y << "\tnear_b_z : " << near_b_z;

    winX = (float)start_x;
    winY = viewport[3] - (float)(start_y + distance_y);

    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &near_c_x, &near_c_y, &near_c_z);
    // qDebug() << "near_c_x : " << near_c_x << "\tnear_c_y : " << near_c_y << "\tnear_c_z : " << near_c_z;

    winX = (float)(start_x + distance_x);
    winY = viewport[3] - (float)(start_y + distance_y);

    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &near_d_x, &near_d_y, &near_d_z);
    // qDebug() << "near_d_x : " << near_d_x << "\tnear_d_y : " << near_d_y << "\tnear_d_z : " << near_d_z;

    winZ = 1;

    winX = (float)start_x;
    winY = viewport[3] - (float)start_y;

    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &far_a_x, &far_a_y, &far_a_z);
    // qDebug() << "far_a_x : " << far_a_x << "\tfar_a_y : " << far_a_y << "\tfar_a_z : " << far_a_z;

    winX = (float)(start_x + distance_x);
    winY = viewport[3] - (float)start_y;

    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &far_b_x, &far_b_y, &far_b_z);
    // qDebug() << "far_b_x : " << far_b_x << "\tfar_b_y : " << far_b_y << "\tfar_b_z : " << far_b_z;

    winX = (float)start_x;
    winY = viewport[3] - (float)(start_y + distance_y);

    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &far_c_x, &far_c_y, &far_c_z);
    // qDebug() << "far_c_x : " << far_c_x << "\tfar_c_y : " << far_c_y << "\tfar_c_z : " << far_c_z;

    winX = (float)(start_x + distance_x);
    winY = viewport[3] - (float)(start_y + distance_y);

    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &far_d_x, &far_d_y, &far_d_z);
    // qDebug() << "far_d_x : " << far_d_x << "\tfar_d_y : " << far_d_y<< "\tfar_d_z : " << far_d_z;

    return;
}

bool Widget::isInner(float x, float y, float z)
{

    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLdouble screen_x, screen_y, screen_z;

    glGetIntegerv(GL_VIEWPORT, viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);

    float winX = x;
    float winY = y;
    float winZ = z;

    gluProject(winX, winY, winZ, modelview, projection, viewport, &screen_x, &screen_y, &screen_z);
    screen_y = viewport[3] - screen_y;

    int int_screen_x = int(round(screen_x));
    int int_screen_y = int(round(screen_y));

    if(int_screen_x >= start_x && int_screen_x <= end_x && int_screen_y >= start_y && int_screen_y <= end_y)
    {
        return true;
    }

    return false;
}

QPoint Widget::getCenter(int width, int height)
{

    if (height == -1)
    {
        height = width;
    }

    qDebug() << "GET CENTER OF AREA : " << width * height;

    QPoint point(0, 0);

    cv::Mat img = cv::imread("/home/elvis/a.png", cv::IMREAD_GRAYSCALE);
    cv::Mat out;

    int rows = img.rows, cols = img.cols;

    int area = width * height;

    if(area > rows * cols)
    {
        area = rows * cols;
    }

    double rate =  1 / (2 + exp( - float(area) / (rows * cols))) + 0.5;

    cv::threshold(img, out, 100, 255, 3);

    cv::PCA::Flags flag = cv::PCA::Flags::DATA_AS_COL;

    flag = cv::PCA::Flags::DATA_AS_ROW;

    cv::PCA pca(out, cv::noArray(), flag, rate);

    cv::Mat project_matrix, result;

    pca.project(out, project_matrix);

    pca.backProject(project_matrix, result);

    result.convertTo(result, CV_8U);

    cv::threshold(result, result, 0, 255, cv::THRESH_BINARY);

    double position_x = 0;
    double position_y = 0;

    int count = 0;

    for(int i = 1; i < rows-1; i++)
    {
        for(int j = 1; j < cols-1; j++)
        {
            uchar character = result.at<uchar>(i, j);

            if (character == 0)
            {
                position_x += i;
                position_y += j;
                count ++;
            }
        }
    }

    if(count == 0)
    {
        point.setX(int(rows / 2));
        point.setX(int(cols / 2));
    }
    else
    {
        point.setX(int(round(position_x / count)));
        point.setY(int(round(position_y / count)));
    }

    cv::Point up, down;

    up.x = point.x() - width / 2;
    up.y = point.y() - height / 2;

    down.x = point.x() + width / 2;
    down.y = point.y() + height / 2;

    if(up.x < 0)
    {
        down.x += abs(up.x);
        up.x = 0;
    }

    if(up.y < 0)
    {
        down.y += abs(up.y);
        up.y = 0;
    }

    if(down.x > rows)
    {
        int distance = rows - down.x;
        up.x -= distance;
        down.x = rows;
    }

    if(down.y > cols)
    {
        int distance = cols - down.y;
        up.y -= distance;
        down.y = cols;
    }

    cv::rectangle(img, up, down, cv::Scalar(0, 255, 0), 4, 8, 0);

    while(true)
    {
        int character = cv::waitKey(100);
        if (character == 27)
        {
            cv::destroyWindow("IMG");
            break;
        }
        else
        {
            imshow("IMG", img);
        }
    }

    return point;
}
