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

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

float red[] = { 1.0f, 0.0f, 0.0f };
float green[] = { 0.0f, 1.0f, 0.0f };
float gray[] = { 0.7f, 0.7f, 0.7f };
float yellow[] = { 1.0f, 0.95f, 0.0f };
float white[] = { 1.0f, 1.0f, 1.0f };
float black[] = { 0.0f, 0.0f, 0.0f };
float background[] = { 0.0f, 0.65f, 0.97f };

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const double VIEWING_Z = -700.0f;

const int MAX_DEPTH = 6;

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

Vector3 lightPosition = Vector3(10, 100, 50);

Vector3 lightTwoPosition = Vector3(-50, 100, 50);

float Ni = 1.0f;

void setMainViewport(int width, int height) {
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-width / 2, width / 2, -height / 2, height / 2);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

bool isEven(int x) {
    return x % 2 == 0;
}

void getRgb(Sphere *sphere, Vector3 point, float rgb[]) {
    float r, g, b;
    Sphere sphere2 = (sphere == largeSphere) ? *smallSphere : *largeSphere;
    
    float La[] = { sphere->ambColor[0] * ambLight[0],
        sphere->ambColor[1] * ambLight[1],
        sphere->ambColor[2] * ambLight[2] };
    
    double ambComponent[] = { sphere->Ka * La[0], sphere->Ka * La[1], sphere->Ka * La[2] };
    
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

        float Li[] = { lightColor[0] * sphere->diffColor[0],
            lightColor[1] * sphere->diffColor[1],
            lightColor[2] * sphere->diffColor[2] };
        float sn = s * n;
        double diffComponent[] = { sphere->Kd * (Li[0] * sn), sphere->Kd * (Li[1] * sn), sphere->Kd * (Li[2] * sn) };

        Li[0] = lightColor[0] * sphere->specColor[0];
        Li[1] = lightColor[1] * sphere->specColor[1];
        Li[2] = lightColor[2] * sphere->specColor[2];
        
        float rvke = powf(ref * v, sphere->Ke);
        double specComponent[] = { sphere->Ks * (Li[0] * rvke), sphere->Ks * (Li[1] * rvke), sphere->Ks * (Li[2] * rvke) };

        r = ambComponent[0] + diffComponent[0] + specComponent[0];
        g = ambComponent[1] + diffComponent[1] + specComponent[1];
        b = ambComponent[2] + diffComponent[2] + specComponent[2];
    }
    
    rgb[0] = r;
    rgb[1] = g;
    rgb[2] = b;
    
    delete(shadowRay);
}

void getRgb(Ray *ray, Sphere *sphere, float rgb[]) {
    Vector3 point = ray->getClosestIntersection(sphere);
    getRgb(sphere, point, rgb);
}

void getRgb(Ray *ray, Plane *plane, float rgb[]) {
    Vector3 point = ray->getClosestIntersection(plane);
    Ray *shadowRay = new Ray(point, lightPosition);
    
    int xRemainder = ((int) point.x) % 15;
    int xRounded = ((int) point.x) - xRemainder;
    
    int zRemainder = ((int) point.z) % 15;
    int zRounded = ((int) point.z) - zRemainder;
    
    // checker pattern
    if ((isEven(xRounded / 2) && isEven(zRounded / 2)) ||
        (!isEven(xRounded / 2) && !isEven(zRounded / 2))) {
        plane->color = red;
    } else {
        plane->color = yellow;
    }
    
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

void illuminate(Ray *ray, int depth, float rgb[]) {
    rgb[0] = background[0];
    rgb[1] = background[1];
    rgb[2] = background[2];
    
    if (ray->intersectsSphere(largeSphere)) {
        Vector3 point = ray->getClosestIntersection(largeSphere);
        
        getRgb(largeSphere, point, rgb);
        
        if (depth < MAX_DEPTH) {
            Vector3 n = point - largeSphere->origin;
            Vector3 i(ray->direction);
            n.normalize();
            
            bool inside = ((-i * n) < 0);
            
            if (largeSphere->Kr > 0.0f && !inside) {
                float newRGB[3];
                Ray *reflection;
                
                point += n * 0.01f;
                
                reflection = new Ray(point, i - 2 * (i * n) * n);
                
                illuminate(reflection, depth + 1, newRGB);
                
                delete(reflection);
                
                rgb[0] += newRGB[0] * largeSphere->Kr;
                rgb[1] += newRGB[1] * largeSphere->Kr;
                rgb[2] += newRGB[2] * largeSphere->Kr;
                
                point -= n * 0.01f;
            }
            
            if (largeSphere->Kt > 0.0f) {
                float newRGB[3];
                Ray *transmission;
                float Nit = Ni / largeSphere->Nt;
                
                if (inside) {
                    Nit = largeSphere->Nt / Ni;
                    n *= -1;
                }
                
                float discriminate = 1 + (pow(Nit, 2) * (pow(-i * n, 2) - 1));
                
                point -= n * 0.001f;
                
                if (discriminate >= 0.0f) {
                    transmission = new Ray(point, Nit * i +
                                            (Nit * (-i * n) -
                                             sqrt(discriminate)) * n
                                           );
                } else {
                    transmission = new Ray(point, i - 2 * (i * n) * n);
                }
                
                illuminate(transmission, depth + 1, newRGB);
                
                delete(transmission);
                
                rgb[0] += newRGB[0] * largeSphere->Kt;
                rgb[1] += newRGB[1] * largeSphere->Kt;
                rgb[2] += newRGB[2] * largeSphere->Kt;
            }
        }
    } else if (ray->intersectsSphere(smallSphere)) {
        Vector3 point = ray->getClosestIntersection(smallSphere);
        
        getRgb(smallSphere, point, rgb);
        
        if (depth < MAX_DEPTH) {
            Vector3 n = point - smallSphere->origin;
            Vector3 i(ray->direction);
            n.normalize();
            bool inside = (-i * n < 0);
            
            if (smallSphere->Kr > 0.0f && !inside) {
                float newRGB[3];
                Ray *reflection;
                
                point += n * 0.01f;
                
                reflection = new Ray(point, i - 2 * (i * n) * n);
                
                illuminate(reflection, depth + 1, newRGB);
                
                delete(reflection);
                
                rgb[0] += newRGB[0] * smallSphere->Kr;
                rgb[1] += newRGB[1] * smallSphere->Kr;
                rgb[2] += newRGB[2] * smallSphere->Kr;
                
                point -= n * 0.01f;
            }
            
            if (smallSphere->Kt > 0.0f) {
                float newRGB[3];
                Ray *transmission;
                float Nit = Ni / smallSphere->Nt;
                
                if (inside) {
                    Nit = smallSphere->Nt / Ni;
                    n *= -1;
                }
                
                float discriminate = 1 + (pow(Nit, 2) * (pow(-i * n, 2) - 1));
                
                point -= n * 0.001f;
                
                if (discriminate >= 0.0f) {
                    transmission = new Ray(point, Nit * i +
                                           (Nit * (-i * n) -
                                            sqrt(discriminate)) * n
                                           );
                } else {
                    transmission = new Ray(point, i - 2 * (i * n) * n);
                }
                
                illuminate(transmission, depth + 1, newRGB);
                
                delete(transmission);
                
                rgb[0] += newRGB[0] * smallSphere->Kt;
                rgb[1] += newRGB[1] * smallSphere->Kt;
                rgb[2] += newRGB[2] * smallSphere->Kt;
            }
        }
    } else if (ray->intersectsPlane(plane)) {
        getRgb(ray, plane, rgb);
    }
}

void shootRays(int width, int height) {
    float rgb[3];
    Ray *ray;
    
    for (int x = -width / 2; x < width / 2; x++) {
        for (int y = -height / 2; y < height / 2; y++) {
            ray = new Ray(cameraPos, Vector3(x, y, VIEWING_Z));
            
            illuminate(ray, 1, rgb);
            
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

    shootRays(width, height);

    glutSwapBuffers();
    //glutPostRedisplay();
}

void init() {
    glClearColor(0.0, 0.65, 0.97, 0.0);
    
    smallSphere = new Sphere(smallSpherePos, SPHERE_RADIUS, white, white, white);
    smallSphere->Kr = 0.75f;
    
    largeSphere = new Sphere(largeSpherePos, SPHERE_RADIUS, gray, white, gray);
    largeSphere->Kr = 0.1f;
    largeSphere->Nt = 0.95f;
    largeSphere->Kt = 0.85f;
    
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
}

void keyPress(unsigned char c, int x, int y) {
    if (c == 'a') {
        lightPosition.y += 10;
    } else if (c == 'z') {
        lightPosition.y -= 10;
    }
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

