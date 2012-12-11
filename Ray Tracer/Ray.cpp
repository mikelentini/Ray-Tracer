//
//  Ray.cpp
//  Ray Tracer
//
//  Created by Mike Lentini on 12/7/12.
//  Copyright (c) 2012 Mike Lentini. All rights reserved.
//

#include "Ray.h"

Ray::Ray(Vector3 origin, Vector3 direction, float distance) {
    this->origin = origin;
    this->direction = direction;
    this->distance = distance;
    
    this->direction.normalize();
}

bool Ray::intersectsSphere(Sphere sphere) {
    //A = Xd^2 + Yd^2 + Zd^2
    //B = 2 * (Xd * (X0 - Xc) + Yd * (Y0 - Yc) + Zd * (Z0 - Zc))
    //C = (X0 - Xc)^2 + (Y0 - Yc)^2 + (Z0 - Zc)^2 - Sr^2
    
    //float a = pow(this->direction.x, 2) + pow(this->direction.y, 2) + pow(this->direction.z, 2);
    float b = 2 * (this->direction.x * (this->origin.x - sphere.x) + this->direction.y *
                   (this->origin.y - sphere.y) + this->direction.z * (this->origin.z - sphere.z));
    float c = pow(this->origin.x - sphere.x, 2) + pow(this->origin.y - sphere.y, 2) +
                    pow(this->origin.z - sphere.z, 2) + pow(sphere.radius, 2);
    
    return ((pow(b, 2) - 4 * c) >= 0);
}

Vector3 Ray::getClosestIntersection(Sphere sphere) {
    //t0 (-), t1 (+) = (- B + (B^2 - 4*C)^1/2) / 2
    // if t0 is positive, use it. else compute t1
    
    //float a = pow(this->direction.x, 2) + pow(this->direction.y, 2) + pow(this->direction.z, 2);
    float b = 2 * (this->direction.x * (this->origin.x - sphere.x) + this->direction.y *
                   (this->origin.y - sphere.y) + this->direction.z * (this->origin.z - sphere.z));
    float c = pow(this->origin.x - sphere.x, 2) + pow(this->origin.y - sphere.y, 2) +
                    pow(this->origin.z - sphere.z, 2) + pow(sphere.radius, 2);
    
    float ti = (-b - (sqrt(pow(b, 2) - 4 * c))) / 2;
    
    if (ti <= 0) {
        ti = (-b + (sqrt(pow(b, 2) - 4 * c))) / 2;
    }
    
    return Vector3(this->origin.x + this->direction.x * ti,
                       this->origin.y + this->direction.y * ti,
                       this->origin.z + this->direction.z * ti);
}

