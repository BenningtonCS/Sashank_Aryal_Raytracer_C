//
// Created by Sashank on 3/9/2016.
//


#include "Sphere.h"
#include <cmath>
#include <assert.h>

    Sphere::Sphere():Shape(0) {
    radius = 1;
    positionCenter = Vector3D(0,0,0);
        color = ColorRGB(0.5,0.5,0.5,1);
}

Sphere::Sphere(double radius, Vector3D position, ColorRGB _color, float ambience):Shape(ambience) {
    this-> radius = radius;
    this-> positionCenter = position;
    this->color = _color;
}

const double Sphere::getRadius() {
    return radius;
}


const Vector3D Sphere::getPosition() {
    return positionCenter;
}


const double Sphere::rayIntersectionDistance(Ray r){
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


const ColorRGB Sphere::getColor() {
    return color;
}


