//
//  Sphere.cpp
//  Ray Tracer
//
//  Mike Lentini
//

#include "Sphere.h"

Sphere::Sphere(Vector3 origin, double radius, float *ambColor, float *specColor, float *diffColor) {
    this->origin = origin;
    this->radius = radius;
    this->ambColor = ambColor;
    this->specColor = specColor;
    this->diffColor = diffColor;
}