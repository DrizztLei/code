#include "bmp.h"
#include "glwidget.h"

#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMouseEvent>
#include <QDebug>
#include <opencv2/opencv.hpp>
#include <GL/glut.h>

#include <iostream>


GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      clearColor(Qt::black),
      xRot(0),
      yRot(0),
      zRot(0),
      program(0)
{
    memset(textures, 0, sizeof(textures));
}

GLWidget::~GLWidget()
{
    makeCurrent();
    vbo.destroy();
    for (int i = 0; i < 6; ++i)
    {
        delete textures[i];
    }
    delete program;
    doneCurrent();
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(200, 200);
}

void GLWidget::rotateBy(int xAngle, int yAngle, int zAngle)
{
    xRot += xAngle;
    yRot += yAngle;
    zRot += zAngle;
    update();
}

void GLWidget::setClearColor(const QColor &color)
{
    clearColor = color;
    update();
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    makeObject();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1

    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    const char *vsrc =
        "attribute highp vec4 vertex;\n"
        "attribute mediump vec4 texCoord;\n"
        "varying mediump vec4 texc;\n"
        "uniform mediump mat4 matrix;\n"
        "void main(void)\n"
        "{\n"
        "    gl_Position = matrix * vertex;\n"
        "    texc = texCoord;\n"
        "}\n";
    vshader->compileSourceCode(vsrc);

    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    const char *fsrc =
        "uniform sampler2D texture;\n"
        "varying mediump vec4 texc;\n"
        "void main(void)\n"
        "{\n"
        "    gl_FragColor = texture2D(texture, texc.st);\n"
        "}\n";
    fshader->compileSourceCode(fsrc);

    program = new QOpenGLShaderProgram;
    program->addShader(vshader);
    program->addShader(fshader);
    program->bindAttributeLocation("vertex", PROGRAM_VERTEX_ATTRIBUTE);
    program->bindAttributeLocation("texCoord", PROGRAM_TEXCOORD_ATTRIBUTE);
    program->link();

    program->bind();
    program->setUniformValue("texture", 0);
}

void GLWidget::paintGL()
{
    qDebug() << "GL PAINT ING";

    glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 m;
    m.ortho(-0.5f, +0.5f, +0.5f, -0.5f, 4.0f, 15.0f);
    m.translate(0.0f, 0.0f, -10.0f);
    m.rotate(xRot / 16.0f, 1.0f, 0.0f, 0.0f);
    m.rotate(yRot / 16.0f, 0.0f, 1.0f, 0.0f);
    m.rotate(zRot / 16.0f, 0.0f, 0.0f, 1.0f);

    program->setUniformValue("matrix", m);
    program->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
    program->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
    program->setAttributeBuffer(PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, 0, 3, 5 * sizeof(GLfloat));
    program->setAttributeBuffer(PROGRAM_TEXCOORD_ATTRIBUTE, GL_FLOAT, 3 * sizeof(GLfloat), 2, 5 * sizeof(GLfloat));

    for (int i = 0; i < 6; ++i)
    {
        textures[i]->bind();
        glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
    }

    qDebug() << "GL PAINT DONE";
}

void GLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton)
    {
        rotateBy(8 * dy, 8 * dx, 0);
    }
    else if (event->buttons() & Qt::RightButton)
    {
        rotateBy(8 * dy, 0, 8 * dx);
    }
    lastPos = event->pos();
}

void GLWidget::mouseReleaseEvent(QMouseEvent * /* event */)
{
    emit clicked();
}

void GLWidget::makeObject()
{
    static const int coords[6][4][3] = {
        { { +1, -1, -1 }, { -1, -1, -1 }, { -1, +1, -1 }, { +1, +1, -1 } },
        { { +1, +1, -1 }, { -1, +1, -1 }, { -1, +1, +1 }, { +1, +1, +1 } },
        { { +1, -1, +1 }, { +1, -1, -1 }, { +1, +1, -1 }, { +1, +1, +1 } },
        { { -1, -1, -1 }, { -1, -1, +1 }, { -1, +1, +1 }, { -1, +1, -1 } },
        { { +1, -1, +1 }, { -1, -1, +1 }, { -1, -1, -1 }, { +1, -1, -1 } },
        { { -1, -1, +1 }, { +1, -1, +1 }, { +1, +1, +1 }, { -1, +1, +1 } }
    };

    for (int j = 0; j < 6; ++j)
    {
        textures[j] = new QOpenGLTexture(QImage(QString(":/images/side%1.png").arg(j + 1)).mirrored());
    }


    QVector<GLfloat> vertData;
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            // vertex position
            vertData.append(0.2 * coords[i][j][0]);
            vertData.append(0.2 * coords[i][j][1]);
            vertData.append(0.2 * coords[i][j][2]);
            // texture coordinate
            vertData.append(j == 0 || j == 3);
            vertData.append(j == 0 || j == 1);
        }
    }

    vbo.create();
    vbo.bind();
    vbo.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));
}

int GLWidget::saveImg(std::string filename, int m_width, int m_height)
{

    makeCurrent();
    int vp[4];
    GLint _currentDrawbuf;
    glGetIntegerv(GL_VIEWPORT, vp);
    glGetIntegerv(GL_DRAW_BUFFER, &_currentDrawbuf); // Save the current Draw buffer

    QObject::connect(this, &GLWidget::resized, [&]()
    {
                         qDebug() << "YOU HAVE REISZED > ";

                         QSize size = GLWidget::size();

                         qDebug() << size.height();
                         qDebug() << size.width();

     });

    this->resizeGL(m_width, m_height);
    this->paintGL();

    rgb_image_struct* output_image = allocate_image(m_width, m_height);
    clear_image(output_image);

    glReadPixels(0, 0, m_width, m_height, GL_RGB, GL_UNSIGNED_BYTE, *output_image->pixel);

    reverse_image_row(output_image);

    write_bmp_image(filename.c_str(), output_image);

    free_image(output_image);
    glDrawBuffer(_currentDrawbuf);

    resizeGL(vp[2], vp[3]);

    return 0;
}

int GLWidget::saveResizeImg(std::string filename, int m_width, int m_height)
{
    makeCurrent();

    int vp[4];
    float vm[16];
    float pj[16];
    GLint _currentDrawbuf;
    rgb_image_struct* output_image = allocate_image(m_width, m_height);

    glGetIntegerv(GL_VIEWPORT, vp);
    glGetIntegerv(GL_DRAW_BUFFER, &_currentDrawbuf); // Save the current Draw buffer
    glGetFloatv(GL_PROJECTION_MATRIX, vm);
    glGetFloatv(GL_MODELVIEW_MATRIX, pj);

    GLuint tftex;
    GLuint tffbo;

    glGenFramebuffers(1, &tffbo);
    glGenTextures(1, &tftex);
    glBindTexture(GL_TEXTURE_2D, tftex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glBindFramebuffer(GL_FRAMEBUFFER_EXT, tffbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, tftex, 0);
    glViewport(0, 0, m_width, m_height);

    resizeGL(m_width, m_height);
    paintGL();

    qDebug() << this->size().height();
    qDebug() << this->size().width();

    glBindFramebuffer(GL_FRAMEBUFFER_EXT, 0); // disable the frame buffer
    glDrawBuffer(_currentDrawbuf);
    glViewport(vp[0], vp[1], vp[2], vp[3]);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glLoadMatrixf(pj);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLoadMatrixf(vm);

    glBindTexture(GL_TEXTURE_2D, tftex);
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, *output_image->pixel);

    std::string outfilepath = filename;

    reverse_image_row(output_image);
    write_bmp_image(outfilepath.c_str(), output_image);
    glDeleteTextures(1, &tftex);
    glDeleteFramebuffers(1, &tffbo);
    free_image(output_image);

    return 0;
}

int GLWidget::saveWithCV(std::__cxx11::string filename, int m_width, int m_height)
{
    makeCurrent();

    int vp[4];
    float vm[16];
    float pj[16];
    GLint _currentDrawbuf;
    rgb_image_struct* output_image = allocate_image(m_width, m_height);

    glGetIntegerv(GL_VIEWPORT, vp);
    glGetIntegerv(GL_DRAW_BUFFER, &_currentDrawbuf); // Save the current Draw buffer
    glGetFloatv(GL_PROJECTION_MATRIX, vm);
    glGetFloatv(GL_MODELVIEW_MATRIX, pj);

    GLuint tftex;
    GLuint tffbo;

    glGenFramebuffers(1, &tffbo);
    glGenTextures(1, &tftex);
    glBindTexture(GL_TEXTURE_2D, tftex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glBindFramebuffer(GL_FRAMEBUFFER_EXT, tffbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, tftex, 0);
    glViewport(0, 0, m_width, m_height);

    /*
      resizeGL(m_width, m_height);
    */

    paintGL();

    glBindFramebuffer(GL_FRAMEBUFFER_EXT, 0); // disable the frame buffer
    glDrawBuffer(_currentDrawbuf);
    glViewport(vp[0], vp[1], vp[2], vp[3]);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glLoadMatrixf(pj);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLoadMatrixf(vm);

    glBindTexture(GL_TEXTURE_2D, tftex);
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, *output_image->pixel);

    std::string outfilepath = filename;

    reverse_image_row(output_image);
    write_bmp_image(outfilepath.c_str(), output_image);

    cv::Mat img = cv::imread(filename);
    cv::Mat out;
    cv::resize(img, out, cv::Size(m_width, m_height), 0, 0, CV_INTER_LINEAR);
    cv::imwrite(filename, out);

    glDeleteTextures(1, &tftex);
    glDeleteFramebuffers(1, &tffbo);
    free_image(output_image);

    return 0;
}

void reshape(int width, int height)
{
    glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window
    glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed
    glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
    gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes
    glMatrixMode(GL_MODELVIEW);// Switch back to the model view matrix, so that we can start drawing shapes correctly
}

void display()
{
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // Clear the background of our window to red
    glClear(GL_COLOR_BUFFER_BIT); //Clear the colour buffer (more buffers later on)
    glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations
    glFlush(); // Flush the OpenGL buffers to the window
}

int GLWidget::test(std::__cxx11::string filename, int m_width, int m_height)
{

    makeCurrent();

    int vp[4];
    float vm[16];
    float pj[16];
    GLint _currentDrawbuf;
    // rgb_image_struct* output_image = allocate_image(m_width, m_height);

    glGetIntegerv(GL_VIEWPORT, vp);
    glGetIntegerv(GL_DRAW_BUFFER, &_currentDrawbuf); // Save the current Draw buffer
    glGetFloatv(GL_PROJECTION_MATRIX, vm);
    glGetFloatv(GL_MODELVIEW_MATRIX, pj);

    GLuint tftex;
    GLuint tffbo;

    glGenFramebuffers(1, &tffbo);
    glGenTextures(1, &tftex);
    glBindTexture(GL_TEXTURE_2D, tftex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glBindFramebuffer(GL_FRAMEBUFFER_EXT, tffbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, tftex, 0);
    glViewport(0, 0, m_width, m_height);

    QPixmap image = QPixmap::grabWidget(this);

    // image = image.scaled(m_width, m_height);

    if(image.save(QString::fromStdString(filename)))
    {
        qDebug() << "save file succeed.";
    }
    else
    {
        qDebug() << "save file failed.";
    }



    /*
    makeCurrent();
    int vp[4];
    GLint _currentDrawbuf;
    glGetIntegerv(GL_VIEWPORT, vp);
    glGetIntegerv(GL_DRAW_BUFFER, &_currentDrawbuf); // Save the current Draw buffer

    GLubyte * bits; //RGB bits
    GLint viewport[4]; //current viewport

    //get current viewport
    glGetIntegerv(GL_VIEWPORT, viewport);

            int w = viewport[2];
            int h = viewport[3];
            qDebug() << w;
            qDebug() << h;
            bits = new GLubyte[w*3*h];

            //read pixel from frame buffer
            glFinish(); //finish all commands of OpenGL
            glPixelStorei(GL_PACK_ALIGNMENT,1); //or glPixelStorei(GL_PACK_ALIGNMENT,4);
            glPixelStorei(GL_PACK_ROW_LENGTH, 0);
            glPixelStorei(GL_PACK_SKIP_ROWS, 0);
            glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
            glReadPixels(0, 0, w, h, GL_BGR_EXT, GL_UNSIGNED_BYTE, bits);

            // cv::Mat point(w, h, CV_8UC);

            for(int i=0; i < h; ++i)
            {
             for(int j=0; j < w; ++j)
             {
                point.data[i * point.step + j * 3 + 0 ] = (unsigned char) (bits[(h-i-1)*3*w + j*3+0]);
                point.data[i * point.step + j * 3 + 1 ] = (unsigned char) (bits[(h-i-1)*3*w + j*3+1]);
                point.data[i * point.step + j * 3 + 2 ] = (unsigned char) (bits[(h-i-1)*3*w + j*3+2]);
             }
            }

            cv::Mat out;
            // cv::resize(point, out, cv::Size(m_width, m_height));
            cv::imwrite(filename, point);

            qDebug() << "save done";

            // delete[] bits;
            */
    return 0;
}

void GLWidget::capturePicture()
{
    qDebug() << "capturing . ";

    makeCurrent();

    /*
    int height = this->height();
    int width = this->width();
    int touchBeginPoint_x = width / 2;
    int touchBeginPoint_y = height / 2;
    int max_x = width;
    int max_y = height;
    int max_z = 0;

    int min_x = 0;
    int min_y = 0;
    int min_z = 0;

    int windowHeight = height;

    qDebug() << "RUN THE CAPTURE PICTURE.";

    GLint viewport[4];
    GLdouble mvmatrix2[16], projmatrix[16];
    GLfloat winx, winy;
    GLdouble posx = 0, posy = 0, posz = 0;
    GLdouble posx1 = 0, posy1 = 0, posz1 = 0;

    // 获取三个矩阵
    glGetIntegerv(GL_VIEWPORT, viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix2);
    glGetDouyingwblev(GL_PROJECTION_MATRIX, projmatrix);

    int size ;

    glGetIntegerv(GL_POINT_SIZE, &size);
    qDebug() << size;

    winx = touchBeginPoint_x;
    winy = windowHeight - touchBeginPoint_y;

    // 获取 Near平面 的三维坐标
    gluUnProject(winx, winy, 0, mvmatrix2, projmatrix, viewport, &posx, &posy, &posz);

    posz = 0;

    // 获取最远点的三维坐标
    gluProject((max_x + min_x) / 2, (max_y + min_y) / 2, max_z, mvmatrix2, projmatrix, viewport, &posx1, &posy1, &posz1);

    // qDebug() << "gluProject: " << posx1 << " " << posy1 << " " << posz1;
    posz += posz1;

    // 获取中间点的三维坐标
    gluProject((max_x + min_x) / 2, (max_y + min_y) / 2, (max_z + min_z) / 2, mvmatrix2, projmatrix, viewport, &posx1, &posy1, &posz1);

    posz += posz1;

    // 获取最近点的三维坐标
    gluProject((max_x + min_x) / 2, (max_y + min_y) / 2, min_z, mvmatrix2, projmatrix, viewport, &posx1, &posy1, &posz1);
    posz += posz1;

    // 获取 z为平均值 的三维坐标
    gluUnProject(winx, winy, posz / 3, mvmatrix2, projmatrix, viewport, &posx, &posy, &posz);
    */

    GLint viewport[4];
    GLdouble mvmatrix2[16], projmatrix[16];
    GLfloat winx, winy, winz;
    GLdouble posx = 0, posy = 0, posz = 0;
    GLdouble posx1 = 0, posy1 = 0, posz1 = 0;

    glGetIntegerv(GL_VIEWPORT, viewport);   /* 获取三个矩阵 */
    glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix2);
    glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);

    return;
}
