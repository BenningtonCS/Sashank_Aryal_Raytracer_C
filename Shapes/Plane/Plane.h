//
// Created by Sashank on 3/9/2016.
/*
 * Regardless of where the ray intersects in the plane, the normal vector is going to be the same, since it is what defines the plane
 */
//

#ifndef RAYTRACERC_PLANE_H
#define RAYTRACERC_PLANE_H

#include "../../Vector3D/Vector3D.h"
#include "../../Color/Color.h"
#include "../Shape.h"
#include "../../Ray/Ray.h"

using namespace Vector;

class Plane: public Shape {
private:
    Vector3D normalOrientationVector;
    Vector3D pointOnPlane;
    ColorRGB colorOfPlane;
public:
    //Constructor methods
    Plane(Vector3D normalOrientationVector, Vector3D pointOnPlane, ColorRGB colorOfPlane, float ambience);

    //Getters
    const Vector3D &getNormalOrientationVector() const;
    const Vector3D &getPointOnPlane() const;
    const ColorRGB getColor();

    //Other methods
    const double rayIntersectionDistance(Ray r);
    const Vector3D getNormalAt(Vector3D point);


    //Irrespective of where the ray intersects the plane, the normal vector is going to be the same
};


#endif //RAYTRACERC_PLANE_H
