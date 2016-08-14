#include <GL/glut.h>

void display();

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glRectf(-.5f , -.5f , .5f , .5f);
    glFlush();
}

int main(int argc , char ** argv)
{
    gluInit(&argc , argv);

    return 0;
}
