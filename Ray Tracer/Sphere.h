//
//  Sphere.h
//  Ray Tracer
//
//  Mike Lentini
//

#ifndef __Ray_Tracer__Sphere__
#define __Ray_Tracer__Sphere__

#include <iostream>
#include "vecmath.h"

class Sphere {
    public:
        Sphere(Vector3 origin, double radius, int *color);
        
        Vector3 origin;
        double radius;
        int *color;
};

#endif /* defined(__Ray_Tracer__Sphere__) */
