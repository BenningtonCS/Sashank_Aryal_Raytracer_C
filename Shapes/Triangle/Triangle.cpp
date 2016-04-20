//
// Created by Sashank on 4/16/2016.
//

#include "Triangle.h"

Triangle::Triangle(const Vector3D &vertexA, const Vector3D &vertexB, const Vector3D &vertexC, ColorRGB &color, float ambience): Shape(ambience) {
    this->vertexA = vertexA;
    this->vertexB = vertexB;
    this->vertexC = vertexC;
    this->colorOfTriangle = color;
}

const ColorRGB Triangle::getColor() {
    return colorOfTriangle;
}

const double Triangle::rayIntersectionDistance(Ray r) {

}

const Vector3D Triangle::getNormalAt(Vector3D point) {
    Vector3D AB = vertexB - vertexA;
    Vector3D AC = vertexC - vertexA;
    return CrossProduct(AB, AC).unitVector();
}

