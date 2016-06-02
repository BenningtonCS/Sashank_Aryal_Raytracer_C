//
// Created by Sashank on 4/16/2016.
//

#ifndef RAYTRACERC_TRIANGLE_H
#define RAYTRACERC_TRIANGLE_H
#include "../../Vector3D/Vector3D.h"
#include "../Shape.h"

using namespace Vector;

class Triangle: public Shape{
private:
    Vector3D vertexA;
    Vector3D vertexB;
    Vector3D vertexC;
    ColorRGB colorOfTriangle;

public:
    Triangle(const Vector3D &vertexA, const Vector3D &vertexB, const Vector3D &vertexC,const Material & material);

    const double rayIntersectionDistance(Ray r);

    const Vector3D getNormalAt(Vector3D point);



};


#endif //RAYTRACERC_TRIANGLE_H
