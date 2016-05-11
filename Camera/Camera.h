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
    SamplingTypes typeOfSampling;
    int numberOfSamples;
    int heightOfScene;
    int widthOfScene;

    double apertureRadius;                            //determines how blur the objects out of focus are
    double focalLength;                             //determines the z-distance in view space which objects will be in focus
    bool depthOfFieldEnabled;
public:
    //Constructors

    Camera(const Vector3D &position, const Vector3D &lookAtPoint);

    Camera(const Vector3D &position, const Vector3D &lookAtPoint, double fov);

    Vector3D getCameraPosition();

    void useSampling(const SamplingTypes typeOfSampling, int numberOfSamples);

    void render(const int width, const int height);

    ColorRGB getColorAt(const Vector3D &intersectionPosition, int indexOfIntersectionPosition);

    Vector3D convertCameraToWorldCoordinates(const Vector3D &v);

    ColorRGB getColorFromRay(const Ray &r);

    ColorRGB getFinalColorFromRandomSampling(int i, int j);

    ColorRGB getFinalColorFromJitteredSampling(int i, int j, std::vector<double> combinationsOfOffsets);

    void useDepthOfField(const double apertureSize, const Vector3D& focalPoint);

    Vector3D randomizeOriginXY();

    Vector3D inverseTransformPoint(const Vector3D & point, int shapeIndex);

    Vector3D inverseTransformDirection(const Vector3D & direction, int shapeIndex);
};
#endif //RAYTRACERC_CAMERA_H
