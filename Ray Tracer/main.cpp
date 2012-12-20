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
#include "Plane.h"

#include <complex>

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

float red[] = { 1.0f, 0, 0 };
float green[] = { 0, 1.0f, 0 };
float yellow[] = { 1.0f, 0.95f, 0 };
float white[] = { 1.0f, 1.0f, 1.0f };
float black[] = { 0.0f, 0.0f, 0.0f };

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const double VIEWING_Z = -700.0f;

Vector3 cameraPos = Vector3(0, 0, 200);

const Vector3 smallSpherePos = Vector3(-55, -25, -115);
const Vector3 largeSpherePos = Vector3(0, 0, -45);
const int SPHERE_RADIUS = 40;
Sphere *smallSphere;
Sphere *largeSphere;

const Vector3 planeNormal = Vector3(0, 1, 0);
const int PLANE_Y = -75;
const int PLANE_MIN_X = -200;
const int PLANE_MAX_X = 110;
Plane *plane;

float ambLight[] = {0.5f, 0.5f, 0.5f};
float lightColor[] = {1.0f, 1.0f, 1.0f};

float Ka = 0.5f;
float Kd = 0.5f;
float Ks = 0.8f;
float Ke = 1.0f;

Vector3 lightPosition = Vector3(100, 100, 50);

void setMainViewport(int width, int height) {
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-width / 2, width / 2, -height / 2, height / 2);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void getRgb(Ray *ray, Sphere *sphere, float rgb[]) {
    float r, g, b;
    Sphere sphere2 = (sphere == largeSphere) ? *smallSphere : *largeSphere;
    
    Vector3 point = ray->getClosestIntersection(sphere);
    float La[] = {sphere->ambColor[0] * ambLight[0],
        sphere->ambColor[1] * ambLight[1],
        sphere->ambColor[2] * ambLight[2]};
    
    double ambComponent[] = {Ka * La[0], Ka * La[1], Ka * La[2]};
    
    Ray *shadowRay = new Ray(point, lightPosition);
    
    if (shadowRay->intersectsSphere(&sphere2)) {
        r = ambComponent[0];
        g = ambComponent[1];
        b = ambComponent[2];
    } else {
        Vector3 s = lightPosition - point;
        Vector3 v = cameraPos - point;
        Vector3 n = point - sphere->origin;

        s.normalize();
        v.normalize();
        n.normalize();

        Vector3 ref = s - 2 * (s * n) * n;
        
        ref.normalize();

        float Li[] = {lightColor[0] * sphere->diffColor[0],
            lightColor[1] * sphere->diffColor[1],
            lightColor[2] * sphere->diffColor[2]};
        float sn = s * n;
        double diffComponent[] = {Kd * (Li[0] * sn), Kd * (Li[1] * sn), Kd * (Li[2] * sn)};

        Li[0] = lightColor[0] * sphere->specColor[0];
        Li[1] = lightColor[1] * sphere->specColor[1];
        Li[2] = lightColor[2] * sphere->specColor[2];
        
        float rvke = powf(ref * v, Ke);

        double specComponent[] = {Ks * (Li[0] * rvke), Ks * (Li[1] * rvke), Ks * (Li[2] * rvke)};

        r = ambComponent[0] + diffComponent[0] + specComponent[0];
        g = ambComponent[1] + diffComponent[1] + specComponent[1];
        b = ambComponent[2] + diffComponent[2] + specComponent[2];
    }
    
    rgb[0] = r;
    rgb[1] = g;
    rgb[2] = b;
    
    delete(shadowRay);
}

void traceRays(int width, int height) {
    float rgb[3];
    Ray *ray;
    
    for (int x = -width / 2; x < width / 2; x++) {
        for (int y = -height / 2; y < height / 2; y++) {
            rgb[0] = 0.0f;
            rgb[1] = 0.65f;
            rgb[2] = 0.97f;
            
            ray = new Ray(cameraPos, Vector3(x, y, VIEWING_Z));
            
            if (ray->intersectsSphere(largeSphere)) {
                getRgb(ray, largeSphere, rgb);
            } else if (ray->intersectsSphere(smallSphere)) {
                getRgb(ray, smallSphere, rgb);
            } else if (ray->intersectsPlane(plane)) {
                Vector3 point = ray->getClosestIntersection(plane);
                Ray *shadowRay = new Ray(point, lightPosition);
                
                if (shadowRay->intersectsSphere(largeSphere) ||
                        shadowRay->intersectsSphere(smallSphere)) {
                    rgb[0] = plane->color[0] * ambLight[0];
                    rgb[1] = plane->color[1] * ambLight[1];
                    rgb[2] = plane->color[2] * ambLight[2];
                } else {
                    rgb[0] = plane->color[0];
                    rgb[1] = plane->color[1];
                    rgb[2] = plane->color[2];
                }
            }
            
            glBegin(GL_POINTS);
                glColor3f(rgb[0], rgb[1], rgb[2]);
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
    
    smallSphere = new Sphere(smallSpherePos, SPHERE_RADIUS, red, white, red);
    largeSphere = new Sphere(largeSpherePos, SPHERE_RADIUS, green, white, green);
    
    plane = new Plane(planeNormal, PLANE_Y, PLANE_MIN_X, PLANE_MAX_X, yellow);
}

void specialKey(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) {
        lightPosition.x -= 10;
    } else if (key == GLUT_KEY_RIGHT) {
        lightPosition.x += 10;
    } else if (key == GLUT_KEY_UP) {
        lightPosition.z -= 10;
    } else if (key == GLUT_KEY_DOWN) {
        lightPosition.z += 10;
    }
    
    cout << lightPosition << endl;
}

void keyPress(unsigned char c, int x, int y) {
    if (c == 'a') {
        lightPosition.y += 10;
    } else if (c == 'z') {
        lightPosition.y -= 10;
    }
    
    cout << lightPosition << endl;
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Ray Tracer");
	glutDisplayFunc(display);
    glutSpecialFunc(specialKey);
    glutKeyboardFunc(keyPress);
    
	init();
    
	glutMainLoop();
}

