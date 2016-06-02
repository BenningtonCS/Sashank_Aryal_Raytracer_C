//
// Created by Sashank on 3/9/2016.
//


#include "Sphere.h"
#include "../../Algebra/Matrix.h"
#include <cmath>
#include <assert.h>

Sphere::Sphere():Shape() {
    radius = 1;
    positionCenter = Vector3D(0,0,0);
}

Sphere::Sphere(const double radius, const Vector3D & position, const Material & material):Shape(material) {
    this-> radius = radius;
    this-> positionCenter = position;
}

const double Sphere::getRadius() {
    return radius;
}


const Vector3D Sphere::getPosition() {
    return positionCenter;
}


const double Sphere::rayIntersectionDistance(Ray r){
    //Transform the ray into local coordinate

    Vector3D L = this->getPosition() - r.getOrigin();
    double t_ca = DotProduct(L, r.getDirection());
    if (t_ca < 0) return -1;
    double d2 = DotProduct(L,L) - t_ca * t_ca;
    if (d2 > radius * radius) return -1;
    double thc = sqrt(radius * radius - d2);
    double t0 = t_ca - thc;
    double t1 = t_ca + thc;
    if (t0 > t1) std::swap(t0, t1);
    if (t0 < 0){
        t0 = t1;
        if (t0 < 0) return -1;
    }
    double t = t0;
    return t;
}

const Vector3D Sphere::getNormalAt(Vector3D point) {
    //normal always points away from the center of the sphere
    return (point - positionCenter).unitVector();
}


