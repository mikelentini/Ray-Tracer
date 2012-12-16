//
//  Sphere.cpp
//  Ray Tracer
//
//  Mike Lentini
//

#include "Sphere.h"

Sphere::Sphere(Vector3 origin, double radius, int *color) {
    this->origin = origin;
    this->radius = radius;
    this->color = color;
}