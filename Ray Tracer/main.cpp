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

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

float red[] = { 1.0f, 0.0f, 0.0f };
float green[] = { 0.0f, 1.0f, 0.0f };
float yellow[] = { 1.0f, 0.95f, 0.0f };

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const float VIEWING_Z = 1.0f;

Sphere *smallSphere;
Sphere *largeSphere;

void setMainViewport(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
	glMatrixMode(GL_MODELVIEW);
}

void traceRays(int width, int height) {
    int size = width * height;
    GLubyte *pixels = new GLubyte[width * height * 3];
    int r, g, b, x, y;
    
    for (int i = 0; i < size; i++) {
        x = i % width;
        y = floor((float) i / (float) width);
        
        r= 255;
        g = 255;
        b = 255;
        
        pixels[(height - y - 1) * 3 * width + x * 3] = r;
        pixels[(height - y - 1) * 3 * width + x * 3 + 1] = g;
        pixels[(height - y - 1) * 3 * width + x * 3 + 2] = b;
    }
    
    glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    
    free(pixels);
}

void display() {
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    
	setMainViewport(width, height);
    
	traceRays(width, height);
    
	glutSwapBuffers();
    //glutPostRedisplay();
}

void init() {
	glClearColor(0.0, 0.65, 1.0, 0.0);
    
    smallSphere = new Sphere(-13, -8, -52, 9, red);
    largeSphere = new Sphere(0, 0, 40, 10, green);
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

