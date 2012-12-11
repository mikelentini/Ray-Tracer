//
//  Sphere.h
//  Ray Tracer
//
//  Created by Mike Lentini on 12/6/12.
//  Copyright (c) 2012 Mike Lentini. All rights reserved.
//

#ifndef __Ray_Tracer__Sphere__
#define __Ray_Tracer__Sphere__

#include <iostream>

class Sphere {
    public:
        Sphere(float x, float y, float z, int radius, float *color);
        
        float x, y, z;
        int radius;
        float *color;
};

#endif /* defined(__Ray_Tracer__Sphere__) */
