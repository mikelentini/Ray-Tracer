//
//  Sphere.cpp
//  Ray Tracer
//
//  Created by Mike Lentini on 12/6/12.
//  Copyright (c) 2012 Mike Lentini. All rights reserved.
//

#include "Sphere.h"

Sphere::Sphere(double x, double y, double z, int radius, int *color) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->radius = radius;
    this->color = color;
}