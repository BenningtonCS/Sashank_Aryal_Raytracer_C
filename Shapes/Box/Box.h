//
// Created by Sashank on 3/26/2016.
//

#ifndef RAYTRACERC_BOX_H
#define RAYTRACERC_BOX_H

#include "../../Vector3D/Vector3D.h"
#include "../Shape.h"

using namespace Vector;

class Box: public Shape {
private:
    //Two bounds representing minimum and maximum extent of the box
    Vector3D bounds[2];

public:
    Box(){};
    Box(const Vector3D &minimumExtent, const Vector3D &maximumExtent, const Material & material);
    const double rayIntersectionDistance(Ray r);
    const Vector3D getNormalAt(Vector3D point);
    void setMinBound(const Vector3D & minB);
    void setMaxBound(const Vector3D & maxB);
};


#endif //RAYTRACERC_BOX_H
