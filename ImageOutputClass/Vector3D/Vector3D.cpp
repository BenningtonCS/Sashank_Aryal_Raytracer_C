//
// Created by Sashank on 3/2/2016.
//
#include "Vector3D.h"

// CONSTRUCTORS IMPLEMENTATION
Vector::Vector3D::Vector3D() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vector::Vector3D::Vector3D(const double _x, const double _y, const double _z) {
    this->x = _x;
    this->y = _y;
    this->z = _z;
}


// GETTERS
const double Vector::Vector3D::getX() const {
    return Vector3D::x;
}

const double Vector::Vector3D::getY() const{
    return Vector3D::y;
}

const double Vector::Vector3D::getZ() const{
    return Vector3D::z;
}

//SETTERS
void Vector::Vector3D::setX(const double x) {
    Vector3D::x = x;
}

void Vector::Vector3D::setY(const double y) {
    Vector3D::y = y;
}

void Vector::Vector3D::setZ(const double z) {
    Vector3D::z = z;
}

//Magnitude
const double Vector::Vector3D::MagnitudeSquared() const{
        return (x * x) + (y * y) + (z * z);
}

const double Vector::Vector3D::Magnitude() const {
    return sqrt(MagnitudeSquared());
}

const Vector::Vector3D Vector::Vector3D::UnitVector() const {
    const double mag = Magnitude();
    return Vector3D(x / mag, y / mag, z / mag);
}


//Operator overloading
Vector::Vector3D &Vector::Vector3D::operator*=(const double factor) {
    x *= factor;
    y *= factor;
    z *= factor;
    return *this;
}
/*
Vector::Vector3D &Vector::Vector3D::operator+=(const Vector::Vector3D &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}
 */
