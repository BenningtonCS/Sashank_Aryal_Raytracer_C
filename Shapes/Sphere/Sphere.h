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
    ColorRGB color;
public:
    //Constructors
    Sphere();
    Sphere(double radius, Vector3D positionCenter, ColorRGB color, float ambience);

    //Getters and setters
    const double getRadius();
    const Vector3D getPosition();
    const ColorRGB getColor();
    const double rayIntersectionDistance(Ray r);
    const Vector3D getNormalAt(Vector3D point);
};
#endif //RAYTRACERC_SPHERE_H
