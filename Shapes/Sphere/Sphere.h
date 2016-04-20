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
    Sphere(double radius, Vector3D positionCenter, ColorRGB _color, float ambience);

    //Getters and setters
    const double getRadius();
    const Vector3D getPosition();
    const double rayIntersectionDistance(Ray r);
    const Vector3D getNormalAt(Vector3D point);
    const ColorRGB getColor();

    //Transformation methods
    const void translateBy(Vector3D coordinate)  {
        return;
    }

    const void scaleBy(Vector3D coordinate)  {
        return;
    }

    const void scaleUniformBy(double factor)  {
        return;
    }

    const void rotateBy(Vector3D d)  {
        return;
    }
};
#endif //RAYTRACERC_SPHERE_H
