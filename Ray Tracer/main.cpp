//
//  main.cpp
//  Ray Tracer
//
//  Mike Lentini
//

#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include "Sphere.h"
#include "Ray.h"

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

int red[] = { 255, 0, 0 };
int green[] = { 0, 255, 0 };
int yellow[] = { 255, 242, 0 };

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const double VIEWING_Z = -700.0f;

const Vector3 cameraPos = Vector3(0, 0, 200);
const Vector3 smallSpherePos = Vector3(-55, -25, -85);
const Vector3 largeSpherePos = Vector3(0, 0, -45);

Sphere *smallSphere;
Sphere *largeSphere;

void setMainViewport(int width, int height) {
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-width / 2, width / 2, -height / 2, height / 2);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void traceRays(int width, int height) {
    int r, g, b;
    Ray *ray;
    
    for (int x = -width / 2; x < width / 2; x++) {
        for (int y = -height / 2; y < height / 2; y++) {
            r = 0;
            g = 165;
            b = 248;
            
            ray = new Ray(cameraPos, Vector3(x, y, VIEWING_Z));
            
            if (ray->intersectsSphere(largeSphere)) {
                r = largeSphere->color[0];
                g = largeSphere->color[1];
                b = largeSphere->color[2];
            } else if (ray->intersectsSphere(smallSphere)) {
                r = smallSphere->color[0];
                g = smallSphere->color[1];
                b = smallSphere->color[2];
            }
            
            glBegin(GL_POINTS);
                glColor3ub(r, g, b);
                glVertex2i(x, y);
            glEnd();
            
            delete(ray);
        }
    }
}

void display() {
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    setMainViewport(width, height);

    traceRays(width, height);

    glutSwapBuffers();
    glutPostRedisplay();
}

void init() {
    glClearColor(0.0, 0.65, 0.97, 0.0);
    
    smallSphere = new Sphere(smallSpherePos, 36, red);
    largeSphere = new Sphere(largeSpherePos, 40, green);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Ray Tracer");
	glutDisplayFunc(display);
    
	init();
    
	glutMainLoop();
}

