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
        Sphere(double x, double y, double z, int radius, int *color);
        
        double x, y, z;
        int radius;
        int *color;
};

#endif /* defined(__Ray_Tracer__Sphere__) */
