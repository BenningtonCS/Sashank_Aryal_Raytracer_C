//
// Created by Sashank on 3/9/2016.
//

#ifndef RAYTRACERC_SHAPE_H
#define RAYTRACERC_SHAPE_H
#include "../Color/Color.h"
#include "../Vector3D/Vector3D.h"
#include "../Ray/Ray.h"

// Base class
class Shape{
public:
    Shape(float amb){ambience = amb;}
    virtual const ColorRGB getColor() = 0;
    virtual const double rayIntersectionDistance(Ray r) = 0;      //Distance from the origin of ray(camera) to the point of intersection
    virtual const Vector3D getNormalAt(Vector3D point) = 0;

    virtual const void translateBy(Vector3D coordinate) = 0;
    virtual const void scaleBy(Vector3D coordinate) = 0;
    virtual const void scaleUniformBy(double factor) = 0;
    virtual const void rotateBy(Vector3D) = 0;

    virtual const float getAmbience(){return this->ambience;};
protected:
    float ambience;
};

#endif //RAYTRACERC_SHAPE_H