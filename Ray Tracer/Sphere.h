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
    
        float Ka = 0.5f;
        float Kd = 0.5f;
        float Ks = 0.3f;
        float Ke = 10.0f;
    
        float Kr = 0.0f;
        float Kt = 0.0f;
    
        float Nt = 0.0f;
};

#endif /* defined(__Ray_Tracer__Sphere__) */
