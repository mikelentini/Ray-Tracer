//
//  main.cpp
//  Ray Tracer
//
//  Mike Lentini
//

#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <cmath>

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

const double VIEWING_Z = -1.0f;

Sphere *smallSphere;
Sphere *largeSphere;

void setMainViewport(int width, int height) {
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void traceRays(int width, int height) {
    int r, g, b;
    Ray *ray;
    
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            r = 0;
            g = 165;
            b = 248;
            
            ray = new Ray(Vector3(0, 0, 0), Vector3(x, y, VIEWING_Z));
            
            if (ray->intersectsSphere(largeSphere)) {
                r = largeSphere->color[0];
                g = largeSphere->color[1];
                b = largeSphere->color[2];
                
                //cout << "hit " << x << ", " << y << endl;
            } else if (ray->intersectsSphere(smallSphere)) {
                r = smallSphere->color[0];
                g = smallSphere->color[1];
                b = smallSphere->color[2];
                
                //cout << "hit" << endl;
            }
            
            glBegin(GL_POINTS);
                glColor3ub(r, g, b);
                glVertex2i(x, y);
            glEnd();
            
            free(ray);
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
    //glutPostRedisplay();
}

void init() {
	glClearColor(0.0, 0.64706, 0.97255, 0.0);
    
    float h2 = WINDOW_HEIGHT / 2;
    float w2 = WINDOW_WIDTH / 2;
    
    //smallSphere = new Sphere(-13, -8, -52, 9, red);
    //largeSphere = new Sphere(0, 0, -40, 10, green);
    smallSphere = new Sphere(w2 - 13, h2 - 8, -52, 9, red);
    largeSphere = new Sphere(w2, h2, -40, 39, green);
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

