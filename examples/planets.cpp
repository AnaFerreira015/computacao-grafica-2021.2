#include<stdlib.h>
#include<GL/glut.h>
#include<algorithm>
#include<iterator>

#define ORANGE  0.8, 0.5, 0.1
#define PURPLE     1.0f, 0.0f, 1.0f
#define CYAN     0.5f, 1.0f, 1.0f
#define GREEN    0.0, 1.0, 0.0
#define GRAY    0.6, 0.6, 0.6

int frame = 0;
double turningSpeed = 1.0;
bool control = false;

// Permite que a animação seja executada
void doFrame(int value) 
{
    glutTimerFunc(10, doFrame, 0);
    //frame++;
    glutPostRedisplay();
}

void reshape(int w, int h) 
{

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(60, (double)w / h, 1, 20);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
}

void keyboard(unsigned char key, int x, int y) 
{
    char OPTIONS[] = { 'y', 'Y' };

    if ((std::find(std::begin(OPTIONS), std::end(OPTIONS), key)) && !control)
    {
        glutTimerFunc(10, doFrame, 1);
        frame++;
    }
    else {
        control = true;
    }
}

void moonX()
{
    glPushMatrix();
    glColor3f(GRAY);
    turningSpeed = 1.5;
    glRotatef(turningSpeed * frame, 0, 1, 0);
    glTranslatef(0.45, 0.1, 0);
    glutSolidSphere(0.05, 100, 100);
    glPopMatrix();
}

void moonY()
{
    glPushMatrix();
    glColor3f(PURPLE);
    turningSpeed = 2.0;
    glRotatef(turningSpeed * frame, 1, 1, 0);
    glTranslatef(0.35, 0, 0);
    glutSolidSphere(0.07, 100, 100);
    glPopMatrix();
}

void planetWithMoons()
{
    glPushMatrix();
    glColor3f(CYAN);
    turningSpeed = 0.5;
    glRotatef(turningSpeed * frame, 0, 1, 0);
    glTranslatef(-2.5, 0.4, -1);
    glPushMatrix();
    glutSolidSphere(0.2, 100, 100);
    glPopMatrix();
}

void mountPlanetWithMoons() 
{
    planetWithMoons();

    moonY();

    moonX();

    glPopMatrix();
}

void sun()
{
    glPushMatrix();
    glColor3f(ORANGE);
    glutSolidSphere(0.5, 100, 100);
    glPopMatrix();
}

void isolatedPlanet()
{
    glPushMatrix();
    glColor3f(GREEN);
    turningSpeed = 2;
    glRotatef(turningSpeed * frame, 0, -1, 0);
    glTranslatef(-1, -0.05, 0);
    glutSolidSphere(0.1, 100, 100);
    glPopMatrix();
}

void solarSystem() 
{
    sun();

    mountPlanetWithMoons();

    isolatedPlanet();
}

void display() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    solarSystem();
    glPopMatrix();

    glutSwapBuffers();
}

void init() 
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(1200, 500);
    glutCreateWindow("Exercício Transformações");
    glutInitWindowPosition(200, 200);

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape); // Remodela a janela atual
    glutMainLoop();

    return 0;
}