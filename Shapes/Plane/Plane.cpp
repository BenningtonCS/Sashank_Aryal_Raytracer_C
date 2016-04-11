//
// Created by Sashank on 3/9/2016.
//

#include "Plane.h"


Plane::Plane(Vector3D normalOrientationVector, Vector3D pointOnPlane, ColorRGB colorOfPlane, float ambience):Shape(ambience) {
    this-> normalOrientationVector = normalOrientationVector;
    this->pointOnPlane = pointOnPlane;
    this->colorOfPlane = colorOfPlane;
}


const Vector3D &Plane::getNormalOrientationVector() const {
    return this->normalOrientationVector;
}

const Vector3D &Plane::getPointOnPlane() const {
    return this->pointOnPlane;
}

const double Plane::rayIntersectionDistance(Ray r){
    //If the dot product of ray direction and normal of plane is zero, the ray is parallel to the plane and they never intersect
    double dotProductOfNormalAndRayDirection = DotProduct(getNormalOrientationVector(), r.getDirection());
    if (dotProductOfNormalAndRayDirection == 0) {
        // Ray does not intersect with the plane. It is parallel.
        //Negative value indicating that the ray did not intersect the plane
        return -1;
    }
    //If the dot product is not zero, the plane’s normal points away from the ray and thus the plane is culled.
    double dotProductOfNormalAndRayOrigin = DotProduct((getPointOnPlane() - r.getOrigin()), getNormalOrientationVector());
        /*
         *
         * ====================COMPUTE THE VALUE OF T====================================
    */
    double numerator = dotProductOfNormalAndRayOrigin;
    double denominator = dotProductOfNormalAndRayDirection;
    double t = numerator / denominator;
    if (t <= 0){
        // intersection point is behind the ray, so no real intersection occurs
        return -1;
    } else {
        return t;
    }

}

const Vector3D Plane::getNormalAt(Vector3D point) {
    return normalOrientationVector;
}


const ColorRGB Plane::getColor() {
    return this->colorOfPlane;
}

