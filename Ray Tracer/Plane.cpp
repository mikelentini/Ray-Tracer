//
//  Plane.cpp
//  Ray Tracer
//
//  Created by Mike Lentini on 12/16/12.
//  Copyright (c) 2012 Mike Lentini. All rights reserved.
//

#include "Plane.h"

Plane::Plane(Vector3 normal, int y, int minX, int maxX, int *color) {
    this->normal = normal;
    this->y = y;
    this->minX = minX;
    this->maxX = maxX;
    this->color = color;
    
    this->normal.normalize();
}