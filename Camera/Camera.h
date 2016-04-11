//
// Created by Sashank on 3/8/2016.
//
#ifndef RAYTRACERC_CAMERA_H
#define RAYTRACERC_CAMERA_H

#include <map>
#include <vector>
#include "../Vector3D/Vector3D.h"
#include "../Ray/Ray.h"
#include "../Color/Color.h"

using namespace Vector;

enum SamplingTypes{
    JITTERED,
    RANDOM
};

class Camera {
private:
    Vector3D position, u, v, w;
    double fov;
    int numberOfSamples;
    SamplingTypes typeOfSampling;
    int heightOfScene;
    int widthOfScene;
public:
    //Constructors
    Camera() {
        useSampling(SamplingTypes::RANDOM, 1);
    }

    Camera(const Vector3D &position, const Vector3D &lookAtPoint);

    Camera(const Vector3D &position, const Vector3D &lookAtPoint, double fov);

    Vector3D getCameraPosition();

    void useSampling(const SamplingTypes typeOfSampling, int numberOfSamples);

    void render(const int width, const int height);

    ColorRGB getColorAt(Vector3D intersectionPosition, int indexOfIntersectionPosition);

    Vector3D convertCameraToWorldCoordinates(Vector3D);

    ColorRGB getColorFromRay(Ray r);

    ColorRGB getFinalColorFromRandomSampling(int i, int j);

    ColorRGB getFinalColorFromJitteredSampling(int i, int j, std::vector<double> combinationsOfOffsets);
};
#endif //RAYTRACERC_CAMERA_H
