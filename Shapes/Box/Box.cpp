//
// Created by Sashank on 3/26/2016.
//

#include "Box.h"
#include "../../Algebra/Algebra.h"
#include "../../Scene/Scene.h"

Box::Box(const Vector3D &minimumExtent, const Vector3D &maximumExtent, const Material & material):Shape(material) {
    bounds[0] = minimumExtent;
    bounds[1] = maximumExtent;
}


const double Box::rayIntersectionDistance(Ray r) {
    double tmin, tmax, tymin, tymax, tzmin, tzmax;

    tmin = Algebra::floatDivision(bounds[0].getX() - r.getOrigin().getX(), r.getDirection().getX());
    tmax = Algebra::floatDivision(bounds[1].getX() - r.getOrigin().getX() ,  r.getDirection().getX());

    if (tmin > tmax) std::swap(tmin, tmax);

    tymin = Algebra::floatDivision(bounds[0].getY() - r.getOrigin().getY() ,  r.getDirection().getY());
    tymax = Algebra::floatDivision(bounds[1].getY() - r.getOrigin().getY() ,  r.getDirection().getY());

    if (tymin > tymax) std::swap(tymin, tymax);
    if ((tmin > tymax) || (tymin > tmax)) return -1;
    if (tymin > tmin) tmin = tymin;
    if (tymax < tmax) tmax = tymax;

    tzmin = Algebra::floatDivision(bounds[0].getZ() - r.getOrigin().getZ() ,  r.getDirection().getZ());
    tzmax = Algebra::floatDivision(bounds[1].getZ() - r.getOrigin().getZ() ,  r.getDirection().getZ());

    if (tzmin > tzmax) std::swap(tzmin, tzmax);
    if ((tmin > tzmax) || (tzmin > tmax)) return -1;
    if (tzmin > tmin) tmin = tzmin;
    if (tzmax < tmax) tmax = tzmax;
    return tmin > tmax ? tmax : tmin;
}

const Vector3D Box::getNormalAt(Vector3D point) {
    const double EPSILON = 0.00001;

    if (std::abs(point.getX() - bounds[0].getX()) < EPSILON) return Vector3D(-1,0,0);

    if (std::abs(point.getX() - bounds[1].getX()) < EPSILON) return Vector3D(1,0,0);

    if (std::abs(point.getY() - bounds[0].getY()) < EPSILON) return Vector3D(0,-1,0);

    if (std::abs(point.getY() - bounds[1].getY()) < EPSILON) return Vector3D(0,1,0);

    if (std::abs(point.getZ() - bounds[0].getZ()) < EPSILON) return Vector3D(0,0,-1);

    if (std::abs(point.getZ() - bounds[1].getZ()) < EPSILON) return Vector3D(0,0,1);

}


void Box::setMinBound(const Vector3D &minB) {
    bounds[0] = minB;
}

void Box::setMaxBound(const Vector3D &maxB) {
    bounds[1] = maxB;
}




