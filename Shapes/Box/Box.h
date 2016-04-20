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
    ColorRGB colorOfBox;

public:
    Box(const Vector3D &minimumExtent, const Vector3D &maximumExtent, ColorRGB color, float ambience);
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


#endif //RAYTRACERC_BOX_H
