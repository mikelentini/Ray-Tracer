//
//  Plane.h
//  Ray Tracer
//
//  Created by Mike Lentini on 12/16/12.
//  Copyright (c) 2012 Mike Lentini. All rights reserved.
//

#ifndef __Ray_Tracer__Plane__
#define __Ray_Tracer__Plane__

#include <iostream>
#include "vecmath.h"

class Plane {
    public:
        Plane(Vector3 normal, int y, int minX, int maxX, float *color);
        
        int y, minX, maxX;
        Vector3 normal;
        float *color;
};

#endif /* defined(__Ray_Tracer__Plane__) */
