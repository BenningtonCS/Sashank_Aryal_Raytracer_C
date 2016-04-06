//
// Created by Sashank on 3/8/2016.
//

#include <math.h>
#include "Vector3D.h"
#include "../Algebra/Algebra.h"

using namespace Vector;
// CONSTRUCTORS IMPLEMENTATION
Vector3D::Vector3D() {
    x = 0;
    y = 0;
    z = 0;
}

Vector3D::Vector3D(const double _x, const double _y, const double _z) {
    this->x = _x;
    this->y = _y;
    this->z = _z;
}


// GETTERS
const double Vector3D::getX() const {
    return Vector3D::x;
}

const double Vector3D::getY() const{
    return Vector3D::y;
}

const double Vector3D::getZ() const{
    return Vector3D::z;
}

//SETTERS
void Vector3D::setX(const double x) {
    Vector3D::x = x;
}

void Vector3D::setY(const double y) {
    Vector3D::y = y;
}

void Vector3D::setZ(const double z) {
    Vector3D::z = z;
}

//magnitude
const double Vector3D::magnitudeSquared() const{
    return (x * x) + (y * y) + (z * z);
}

const double Vector3D::magnitude() const {
    return sqrt(magnitudeSquared());
}

const Vector3D Vector::Vector3D::unitVector() const {
    const double mag = magnitude();
    return Vector3D(Algebra::floatDivision(x, mag), Algebra::floatDivision(y, mag), Algebra::floatDivision(z, mag));
}
