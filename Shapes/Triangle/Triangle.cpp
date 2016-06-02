//
// Created by Sashank on 4/16/2016.
//

#include "Triangle.h"

Triangle::Triangle(const Vector3D &vertexA, const Vector3D &vertexB, const Vector3D &vertexC,const Material & material): Shape(material) {
    this->vertexA = vertexA;
    this->vertexB = vertexB;
    this->vertexC = vertexC;
}


//    HELP TAKEN FROM SCRATCH PIXEL FOR THIS RAY_TRIANGLE INTERSECTION
const double Triangle::rayIntersectionDistance(Ray r) {
    
    // compute plane's normal
    Vector3D vA_vB = vertexA - vertexB;
    Vector3D vA_vC = vertexC - vertexA;
    Vector3D N = CrossProduct(vA_vB, vA_vC);
    double area2 = N.magnitude();

    // Step 1: find P
    // check if ray and plane are parallel
    double NdotRayDirection = DotProduct(N, r.getDirection());
    if (fabs(NdotRayDirection) < 0.000001) // almost 0
        return -1; // they are parallel so they don't intersect !

    // compute d parameter using equation 2
    double d = DotProduct(N, vertexA);

    // compute t (equation 3)
    double t = (DotProduct(r.getOrigin(), N) + d) / NdotRayDirection;
    // check if the triangle is in behind the ray
    if (t < 0) return -1; // the triangle is behind

    // compute the intersection point using equation 1
    Vector3D P = r.getOrigin() + t * r.getDirection();

    
    // Step 2: inside-outside test
    // edge 0
    Vector3D edge0 = vertexB - vertexA;
    Vector3D vp0 = P - vertexA;
    Vector3D C = CrossProduct(edge0, vp0);  // vector perpendicular to triangle's plane
    if (DotProduct(N, C) < 0) return -1; // P is on the right side

    // edge 1
    Vector3D edge1 = vertexC - vertexB;
    Vector3D vp1 = P - vertexB;
    C = CrossProduct(vp1, edge1);
    double u = C.magnitude() / area2;
    if (DotProduct(N, C) < 0)  return -1; // P is on the right side

    // edge 2
    Vector3D edge2 = vertexA - vertexC;
    Vector3D vp2 = P - vertexC;
    C = CrossProduct(edge2, vp2);
    double v = C.magnitude() / area2;
    if (DotProduct(N, C) < 0) return -1; // P is on the right side;

    return t; // this ray hits the triangle
}

const Vector3D Triangle::getNormalAt(Vector3D point) {
    Vector3D AB = vertexB - vertexA;
    Vector3D AC = vertexC - vertexA;
    return CrossProduct(AB, AC).unitVector();
}

