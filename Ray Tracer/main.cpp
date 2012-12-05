//
//  main.cpp
//  Ray Tracer 1
//
//  Mike Lentini
//

#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

const float INTENSITY = 1.0f;

float specLight[] = { INTENSITY, INTENSITY, INTENSITY, 1.0f };
float lightPos[] = { 2.0f, 10.0f, 10.0f, 1.0f };
float diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float ambLight[] = { 0.1f, 0.1f, 0.1f, 1.0f };

float red[] = { 1.0f, 0.0f, 0.0f };
float green[] = { 0.0f, 1.0f, 0.0f };
float yellow[] = { 1.0f, 0.95f, 0.0f };

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

float angle = 0;

void setMainViewport(int width, int height) {
    float aspectRatio = (float) width / (float) height;
    angle += 0.02f;
    
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
	gluPerspective(60, aspectRatio, 0.5f, 200);
	glMatrixMode(GL_MODELVIEW);
}

void display() {
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    
	setMainViewport(width, height);
    
	GLUquadric *closeSphere = gluNewQuadric();
    GLUquadric *farSphere = gluNewQuadric();
    
    gluQuadricNormals(closeSphere, GLU_SMOOTH);
    gluQuadricNormals(farSphere, GLU_SMOOTH);
    
    glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, red);
        
        glTranslatef(0, 0, -40);
        gluSphere(closeSphere, 10, 40, 40);
    glPopMatrix();
    
    glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, green);
        
        glTranslatef(-13, -8, -52);
    
        gluSphere(farSphere, 9, 40, 40);
    glPopMatrix();
    
    gluDeleteQuadric(closeSphere);
    gluDeleteQuadric(farSphere);
    
    glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, yellow);
        
        glBegin(GL_QUADS);
            glVertex3i(-50, -20, 0);
            glVertex3i(28, -20, 0);
            glVertex3i(28, -20, -200);
            glVertex3i(-50, -20, -200);
        glEnd();
    glPopMatrix();
    
	glutSwapBuffers();
    glutPostRedisplay();
}

void init() {
	glClearColor(0.0, 0.65, 1.0, 0.0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
    glEnable(GL_LIGHTING);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambLight);
    
	glEnable(GL_LIGHT0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Ray Tracer");
	glutDisplayFunc(display);
    
	init();
    
	glutMainLoop();
}

