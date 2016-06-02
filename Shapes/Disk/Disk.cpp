//
// Created by Sashank on 3/23/2016.
//

#include "Disk.h"
#include "../Plane/Plane.h"


const double Disk::rayIntersectionDistance(Ray r) {
    //Check if the normal of the disk is parallel to the ray by computing the dot product of ray and normal of disk.
    //They are parallel if the dot product is zero.
    //Perform the test that we did in the plane
    Plane * p = new Plane(normalOrientationVector,centerOfDisk, Material());
    double diskRayIntersectionDistance = p->rayIntersectionDistance(r);
    if (diskRayIntersectionDistance == -1) {  //if ray does not hit plane of disk
        delete p;
        return -1;
    }

    Vector3D pointOfIntersectionInPlane = r.getOrigin() + diskRayIntersectionDistance * r.getDirection();
    if ((pointOfIntersectionInPlane - getCenterOfDisk()).magnitude() <= getRadiusOfDisk()){
        delete p;
        return diskRayIntersectionDistance;
    }
    delete p;
    return -1;

}

const Vector3D Disk::getNormalAt(Vector3D) {
    return normalOrientationVector.unitVector();
}

Vector3D Disk::getCenterOfDisk() {
    return centerOfDisk;
}

double Disk::getRadiusOfDisk() {
    return radiusOfDisk;
}




