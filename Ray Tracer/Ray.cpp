//
//  Ray.cpp
//  Ray Tracer
//
//  Mike Lentini
//

#include "Ray.h"

Ray::Ray(Vector3 origin, Vector3 direction) {
    this->origin = origin;
    this->direction = direction;
    
    this->direction.normalize();
}

bool Ray::intersectsSphere(Sphere *sphere) {
    //A = Xd^2 + Yd^2 + Zd^2 = 1 if d is normalized
    //B = 2 * (Xd * (X0 - Xc) + Yd * (Y0 - Yc) + Zd * (Z0 - Zc))
    //C = (X0 - Xc)^2 + (Y0 - Yc)^2 + (Z0 - Zc)^2 - Sr^2
    double x = this->origin.x - sphere->origin.x;
    double y = this->origin.y - sphere->origin.y;
    double z = this->origin.z - sphere->origin.z;
    
    double b = 2 * (this->direction.x * x + this->direction.y * y + this->direction.z * z);
    double c = (x * x) + (y * y) + (z * z) - (sphere->radius * sphere->radius);
    
    double ti = (-b - sqrt(b * b - 4 * c)) / 2;
    
    if (ti <= 0) {
        ti = (-b + sqrt(b * b - 4 * c)) / 2;
    }
    
    return (ti > 0);
}

Vector3 Ray::getClosestIntersection(Sphere *sphere) {
    //t0 (-), t1 (+) = (-B +- (B^2 - 4*C)^1/2) / 2
    // if t0 is positive, use it. else compute t1
    
    double x = this->origin.x - sphere->origin.x;
    double y = this->origin.y - sphere->origin.y;
    double z = this->origin.z - sphere->origin.z;
    
    double b = 2 * (this->direction.x * x + this->direction.y * y + this->direction.z * z);
    double c = (x * x) + (y * y) + (z * z) - (sphere->radius * sphere->radius);
    
    double ti = (-b - sqrt(b * b - 4 * c)) / 2;
    
    if (ti <= 0) {
        ti = (-b + sqrt(b * b - 4 * c)) / 2;
    }
    
    return Vector3(this->origin.x + this->direction.x * ti,
                       this->origin.y + this->direction.y * ti,
                       this->origin.z + this->direction.z * ti);
}

bool Ray::intersectsPlane(Plane *plane) {
    double w =  -(plane->normal * this->origin + abs(plane->y)) / (plane->normal * this->direction);
    
    if (w <= 0) return false;
    
    Vector3 point = Vector3(this->origin.x + this->direction.x * w,
                                 this->origin.y + this->direction.y * w,
                                 this->origin.z + this->direction.z * w);
    
    return !(point.x > plane->maxX || point.x < plane->minX || point.z < -1250 || point.z > 50);
}

Vector3 Ray::getClosestIntersection(Plane *plane) {
    double w =  -(plane->normal * this->origin + abs(plane->y)) / (plane->normal * this->direction);
    
    return Vector3(this->origin.x + this->direction.x * w,
                            this->origin.y + this->direction.y * w,
                            this->origin.z + this->direction.z * w);
}

