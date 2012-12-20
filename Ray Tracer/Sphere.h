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
        Sphere(Vector3 origin, double radius, float *ambColor, float *specColor, float *diffColor);
        
        Vector3 origin;
        double radius;
        float *ambColor;
        float *specColor;
        float *diffColor;
};

#endif /* defined(__Ray_Tracer__Sphere__) */
