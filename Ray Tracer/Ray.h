//
//  Ray.h
//  Ray Tracer
//
//  Created by Mike Lentini on 12/7/12.
//  Copyright (c) 2012 Mike Lentini. All rights reserved.
//

#ifndef __Ray_Tracer__Ray__
#define __Ray_Tracer__Ray__

#include "vecmath.h"
#include "Sphere.h"

class Ray {
    public:
        Ray(Vector3 origin, Vector3 vector, float distance);
    
        Vector3 direction, origin;
        float distance;
    
        bool intersectsSphere(Sphere sphere);
        Vector3 getClosestIntersection(Sphere sphere);
};

#endif /* defined(__Ray_Tracer__Ray__) */
