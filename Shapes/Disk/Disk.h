//
// Created by Sashank on 3/23/2016.
//

#ifndef RAYTRACERC_DISK_H
#define RAYTRACERC_DISK_H


#include "../../Color/Color.h"
#include "../../Vector3D/Vector3D.h"
#include "../Shape.h"

using namespace Vector;

class Disk: public Shape {
private:
    Vector3D normalOrientationVector;
    Vector3D centerOfDisk;
    double radiusOfDisk;
    ColorRGB colorOfDisk;
public:

    //Constructor
    Disk(const Vector3D &normalOrientationVector, const Vector3D &centerOfDisk, double radiusOfDisk,
         const ColorRGB &colorOfDisk, float ambience) : normalOrientationVector(normalOrientationVector), centerOfDisk(centerOfDisk),
                                        radiusOfDisk(radiusOfDisk), colorOfDisk(colorOfDisk), Shape(ambience) { }

    const double rayIntersectionDistance(Ray r);
    const Vector3D getNormalAt(Vector3D);
    Vector3D getCenterOfDisk();
    double getRadiusOfDisk();
    const ColorRGB getColor();


};


#endif //RAYTRACERC_DISK_H
