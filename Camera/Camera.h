//
// Created by Sashank on 3/8/2016.
//

#ifndef RAYTRACERC_CAMERA_H
#define RAYTRACERC_CAMERA_H

#include "../Vector3D/Vector3D.h"
#include "../Ray/Ray.h"
#include "../Color/Color.h"

using namespace Vector;

class Camera{
private:
    Vector3D position, u, v, w;
    double fov;
public:
    //Constructors
    Camera(){}
    Camera(const Vector3D &position, const Vector3D &lookAtPoint);
    Camera(const Vector3D &position, const Vector3D &lookAtPoint, double fov);

    Vector3D getCameraPosition();

    void render(const int width, const int height);
    ColorRGB getColorAt(Vector3D intersectionPosition, int lowestTPosition);
    Vector3D convertCameraToWorldCoordinates(Vector3D);
};


#endif //RAYTRACERC_CAMERA_H
