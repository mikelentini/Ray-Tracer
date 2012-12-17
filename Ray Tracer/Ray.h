//
//  Ray.h
//  Ray Tracer
//
//  Mike Lentini
//

#ifndef __Ray_Tracer__Ray__
#define __Ray_Tracer__Ray__

#include "vecmath.h"
#include "Sphere.h"
#include "Plane.h"

class Ray {
    public:
        Ray(Vector3 origin, Vector3 vector);
    
        Vector3 direction, origin;
    
        bool intersectsSphere(Sphere *sphere);
        Vector3 getClosestIntersection(Sphere *sphere);
    
        bool intersectsPlane(Plane *plane);
};

#endif /* defined(__Ray_Tracer__Ray__) */
