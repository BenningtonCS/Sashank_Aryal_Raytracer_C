//
// Created by Sashank on 3/8/2016.
//
#pragma once
#ifndef RAYTRACERC_CAMERA_H
#define RAYTRACERC_CAMERA_H

#include <map>
#include <vector>
#include <memory>
#include "../Vector3D/Vector3D.h"
#include "../Ray/Ray.h"
#include "../Color/Color.h"
#include "../Algebra/Matrix.h"
#include "../Algebra/Algebra.h"
#include "../Shapes/Shape.h"
#include "../Lights/Light.h"

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
    int MAX_TRACE_DEPTH;
    std::vector<std::shared_ptr<Shape>> shapes;
    std::vector<std::shared_ptr<Light>> lights;
public:
    //Constructors
    Camera(){};
    Camera(const Vector3D &position, const Vector3D &lookAtPoint);

    Camera(const Vector3D &position, const Vector3D &lookAtPoint, double fov);

    Vector3D getCameraPosition();

    void useSampling(const SamplingTypes typeOfSampling, int numberOfSamples);

    void render(const int width, const int height, std::vector<std::shared_ptr<Shape>> shapes, std::vector<std::shared_ptr<Light>> lights);

    ColorRGB getColorAt(const Vector3D &intersectionPosition, int indexOfIntersectionPosition, int depth);

    Vector3D convertCameraToWorldCoordinates(const Vector3D &v);

    ColorRGB getColorFromRay(const Ray &r, int depth);

    ColorRGB getFinalColorFromSampling(int i, int j, std::vector<double> combinationsOfOffsets);

    void useDepthOfField(const double apertureSize, const Vector3D& focalPoint);

    Vector3D randomizeOriginXY();

    Vector3D transformPoint(const Matrix4x4 & tm, const Vector3D & point);

    Vector3D transformDirection(const Matrix4x4 & tm, const Vector3D & direction);

    Vector3D getReflectedLightDirection(const Vector3D& normal, const Vector3D& incidentLightDirection);

    void setMaxDepth(int maxDepth);

};
#endif //RAYTRACERC_CAMERA_H
