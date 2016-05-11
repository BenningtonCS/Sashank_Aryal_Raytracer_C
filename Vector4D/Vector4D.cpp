//
// Created by Sashank on 5/3/2016.
//

#include "Vector4D.h"
#include "../Algebra/Algebra.h"

using namespace Vector;
// CONSTRUCTORS IMPLEMENTATION
Vector4D::Vector4D() {
    x = 0;
    y = 0;
    z = 0;
    w = 0;
}

Vector4D::Vector4D(const double _x, const double _y, const double _z, const double _w) {
    this->x = _x;
    this->y = _y;
    this->z = _z;
    this->w = _w;
}


// GETTERS
const double Vector4D::getX() const {
    return Vector4D::x;
}

const double Vector4D::getY() const{
    return Vector4D::y;
}

const double Vector4D::getZ() const{
    return Vector4D::z;
}

const double Vector4D::getW() const{
    return Vector4D::w;
}
//magnitude
const double Vector4D::magnitudeSquared() const{
    return (x * x) + (y * y) + (z * z);
}

const double Vector4D::magnitude() const {
    return sqrt(magnitudeSquared());
}


