#include <GL/glut.h>
#include <stdlib.h>
/*
  funtion head
*/
void init();
void display();
void reshape(int w , int h);
void keyboard(unsigned char key , int x , int y);
int main(int argc , char ** argv);

/*
  function body
*/
// init the params
void init()
{
    GLfloat mat_specular[] = {1 , 1 , 1, 1};
    GLfloat mat_shininess[] = {50};
    GLfloat light_position[] = {1 , 1 , 1 , 1};

    glClearColor(0, 0, 0, 0);
    glShadeModel(GL_SMOOTH);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glEnable (GL_DEPTH_TEST);
}

// call the function glut to draw a ball
void display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSolidSphere(1 , 40 , 50);
    glFlush();
}

void reshape(int w , int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(w < h)
    {
        glOrtho(-1.5,
                1.5,
                -1.5 * (GLfloat) h /(GLfloat)w,
                1.5*(GLfloat)h / (GLfloat)w,
                -10,
                10);
        glOrtho (-1.5 * ( GLfloat ) w / ( GLfloat ) h,
                 1.5 * ( GLfloat ) w / ( GLfloat ) h,
                 -1.5,
                 1.5,
                 -10.0,
                 10.0);
        glMatrixMode ( GL_MODELVIEW );
        glLoadIdentity () ;
    }
}

void keyboard(unsigned char key , int x , int y)
{
    switch(key)
    {
    case 27: exit(0);
        break;
    }
}


int main(int argc , char ** argv)
{
    glutInit(& argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
