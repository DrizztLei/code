#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QOpenGLWidget>

namespace Ui
{
    class Widget;
}

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)
QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)

class Widget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
public:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void capture(int start_x , int start_y, int end_x, int end_y);
    bool isInner(float x, float y, float z);
    QPoint getCenter(int width, int height = -1);
    
private:
    void draw();
    int faceAtPosition(const QPoint &pos);
    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;
    QColor faceColors[4];
    QPoint lastPos;

private:
    Ui::Widget *ui;
    GLdouble translateX, translateY, translateZ;
    GLdouble scaledX, scaledY, scaledZ;
    GLdouble rotateAngle, rotateX, rotateY, rotateZ;
    GLdouble depth_near, depth_far;

    GLdouble near_a_x, near_a_y, near_a_z;
    GLdouble near_b_x, near_b_y, near_b_z;
    GLdouble near_c_x, near_c_y, near_c_z;
    GLdouble near_d_x, near_d_y, near_d_z;

    GLdouble far_a_x, far_a_y, far_a_z;
    GLdouble far_b_x, far_b_y, far_b_z;
    GLdouble far_c_x, far_c_y, far_c_z;
    GLdouble far_d_x, far_d_y, far_d_z;
    GLsizei gl_size;
    GLuint* select_buffer;

    int start_x;
    int start_y;
    int end_x;
    int end_y;

};

#endif // WIDGET_H
