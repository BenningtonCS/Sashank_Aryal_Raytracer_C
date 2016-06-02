//
// Created by Sashank on 3/9/2016.
//

#ifndef RAYTRACERC_SPHERE_H
#define RAYTRACERC_SPHERE_H

#include "../Shape.h"
#include "../../Vector3D/Vector3D.h"
#include "../../Ray/Ray.h"

using namespace Vector;

class Sphere: public Shape {                //Class sphere inherits from the abstract class shape
private:
    double radius;
    Vector3D positionCenter;
public:
    //Constructors
    Sphere();
    Sphere(const double radius, const Vector3D & positionCenter, const  Material & material);

    //Getters and setters
    const double getRadius();
    const Vector3D getPosition();

    void setRadius(double radius) {
        Sphere::radius = radius;
    }

    void setPosition(const Vector3D &positionCenter) {
        Sphere::positionCenter = positionCenter;
    }

    const double rayIntersectionDistance(Ray r);
    const Vector3D getNormalAt(Vector3D point);
};
#endif //RAYTRACERC_SPHERE_H
