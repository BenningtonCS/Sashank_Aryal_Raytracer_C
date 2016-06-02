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
public:
    //Constructor methods
    Plane(){};
    Plane(const Vector3D & normalOrientationVector, const Vector3D & pointOnPlane,const Material & material);

    //Getters
    const Vector3D &getNormalOrientationVector() const;
    const Vector3D &getPointOnPlane() const;
    //Other methods
    const double rayIntersectionDistance(Ray r);
    //Irrespective of where the ray intersects the plane, the normal vector is going to be the same
    const Vector3D getNormalAt(Vector3D point);


    void setNormalOrientationVector(const Vector3D &normalOrientationVector) {
        Plane::normalOrientationVector = normalOrientationVector;
    }

    void setPointOnPlane(const Vector3D &pointOnPlane) {
        Plane::pointOnPlane = pointOnPlane;
    }
};


#endif //RAYTRACERC_PLANE_H
