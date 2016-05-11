//
// Created by Sashank on 3/26/2016.
//


#include <cstring>
#include "Camera.h"
#include "../Scene/Scene.h"
#include "../Image/CreateImage.h"
#include "../Algebra/Algebra.h"

Camera::Camera(const Vector3D &position, const Vector3D &lookAtPoint) {
    this->position = position;
    Vector3D differenceBetweenImageAndCamera = lookAtPoint - position;       //The difference between the camera and the point where we want to look
    bool cameraIsLookingFromTop = (position.getX() == 0 && position.getZ() == 0 && position.getY() != 0);

    // CREATE A VIRTUAL COORDINATE SYSTEM FOR THE CAMERA. IN ORTHONORMAL BASIS
    w = differenceBetweenImageAndCamera.unitVector();                           //Normalize the difference and make it positive by multiplying with -1
    u = !cameraIsLookingFromTop ? CrossProduct(Vector3D(0,1,0),w).unitVector() : CrossProduct(Vector3D(-1,0,0),w).unitVector();
    v = CrossProduct(w, u);
    fov = 52.0;
    useSampling(SamplingTypes::RANDOM, 1);
    depthOfFieldEnabled = false;
}


Camera::Camera(const Vector3D &position, const Vector3D &lookAtPoint, double fov):
    Camera(position, lookAtPoint) {
        this->fov = fov;
    }

Vector3D Camera::convertCameraToWorldCoordinates(const Vector3D &point) {
    return ((point.getX() * u + (point.getY() * v) + (point.getZ() * w)));
}


void Camera::render(const int width, const int height) {
    heightOfScene = height;
    widthOfScene = width;
    int resolution = width * height;
    ColorRGB *pixels = new ColorRGB[resolution];
    long loopCounter = 0;

    std::vector<double> combinationsOfOffSets;
    if (typeOfSampling == SamplingTypes::JITTERED){
        for (int index = 0; index < numberOfSamples; index++){
            combinationsOfOffSets.emplace_back((double)(2 * index + 1) / (2 * numberOfSamples));
        }
    }

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (typeOfSampling == SamplingTypes::RANDOM){
                pixels[loopCounter] = getFinalColorFromRandomSampling(i, j);
            } else {
                pixels[loopCounter] = getFinalColorFromJitteredSampling(i , j, combinationsOfOffSets);
            }
            loopCounter++;
        }
    }
    CreateImage::createRasterImage(height, width, "RenderedImage.bmp", pixels);
    delete [] pixels;      //Release memory
}

ColorRGB Camera::getFinalColorFromJitteredSampling(int i, int j, std::vector<double> combinationsOfOffsets){
    ColorRGB finalColor = ColorRGB(0,0,0,0);
    double wCamDir = depthOfFieldEnabled ? focalLength : 1;
    double pixelSize =  tan(Algebra::deg2rad(fov * 0.5)) * wCamDir / (heightOfScene/2);

    for (int multiSamplingLoopIndex = 0 ; multiSamplingLoopIndex < (numberOfSamples * numberOfSamples); multiSamplingLoopIndex++) {
        double uOffset = combinationsOfOffsets[multiSamplingLoopIndex % numberOfSamples];
        double vOffset = combinationsOfOffsets[multiSamplingLoopIndex / numberOfSamples];

        double uCamDir = ((i - (widthOfScene / 2)) + (numberOfSamples == 1 ? 0.5 : uOffset)) * pixelSize;
        double vCamDir = (((heightOfScene / 2) - j) + (numberOfSamples == 1 ? 0.5 : vOffset)) * pixelSize;

        //Also randomize origin if depth of field has been used

        Vector3D camRayOrigin = !depthOfFieldEnabled ? Vector3D() : randomizeOriginXY();
        Vector3D camRayDirection = Vector3D (uCamDir, vCamDir, wCamDir) - camRayOrigin;

        camRayDirection = convertCameraToWorldCoordinates(camRayDirection).unitVector();
        camRayOrigin = convertCameraToWorldCoordinates(camRayOrigin) + getCameraPosition();

        Ray r(camRayOrigin, camRayDirection);
        finalColor = finalColor + getColorFromRay(r);
    }
    return finalColor / (numberOfSamples * numberOfSamples);
}

ColorRGB Camera::getFinalColorFromRandomSampling(int i, int j){
    ColorRGB finalColor = ColorRGB(0,0,0,0);
    double zCamDir = (heightOfScene/2) / tan(Algebra::deg2rad(fov * 0.5));
    for (int k = 0 ; k < numberOfSamples; k++) {
        //If it is single sampled, then we want to cast ray in the middle of the pixel, otherwise we offset the ray by a random value between 0-1
        double randomNumber = Algebra::getRandomBetween(0,1);
        double xCamDir = (i - (widthOfScene / 2)) + (numberOfSamples == 1 ? 0.5 : randomNumber);
        double yCamDir = ((heightOfScene / 2) - j) + (numberOfSamples == 1 ? 0.5 : randomNumber);
        Vector3D camRayDirection = convertCameraToWorldCoordinates(Vector3D(xCamDir, yCamDir, zCamDir)).unitVector();
        Ray r(getCameraPosition(), camRayDirection);
        finalColor = finalColor + getColorFromRay(r);
    }
    return finalColor / numberOfSamples;
}


ColorRGB Camera::getColorFromRay(const Ray &r){
    // Render all objects that are inside the shape container
    // If more than one object is hit, the one with the intersection point closer to the observer commands the pixel color,
    int numberOfObjectsToRender = (int) Scene::shapes.size();
    int lowestTposition = 0;

    double leastValueOfT = 100000000;
    Ray intersectingTransformedRay = r;
    for (int l = 0; l < numberOfObjectsToRender; ++l) {
        //Convert ray to the new coordinate space
        Vector3D newRayOrigin = inverseTransformPoint(r.getOrigin(), l);
        Vector3D newRayDirection = inverseTransformDirection(r.getDirection(), l);
        Ray newRay(newRayOrigin, newRayDirection);
        intersectingTransformedRay = newRay;
        double intersectionDistance = Scene::shapes[l]->rayIntersectionDistance(newRay);
        if (intersectionDistance > 0.000001 && intersectionDistance < leastValueOfT) {  //0.000001 for accuracy purpose
            leastValueOfT = intersectionDistance;
            lowestTposition = l;
        }
    }

    if ( leastValueOfT < 100000000) {
        Vector3D intersectingPosition = intersectingTransformedRay.getOrigin() + leastValueOfT * intersectingTransformedRay.getDirection();
        //find P in another coordinate system
        Vector3D realIntersectingPosition = Scene::shapes[lowestTposition]->getTransformationMatrix() * intersectingPosition;
        return getColorAt(realIntersectingPosition, lowestTposition);
    }
    return ColorRGB();
}

ColorRGB Camera::getColorAt(const Vector3D &intersectionPosition, int indexOfIntersectionPosition) {
    ColorRGB finalColor(0,0,0,0);
    ColorRGB colorOfObject = Scene::shapes[indexOfIntersectionPosition]->getColor();
    for (int i = 0; i < Scene::lights.size(); i++) {
        bool isShadowed = false;
        double distanceBetweenLightAndObject = 10000000000;
        if (Scene::lights[i]->getLightType() == TypesOfLight::POINTLIGHT)
            distanceBetweenLightAndObject = std::abs((Scene::lights[i]->getLightPosition() - intersectionPosition).magnitude());
        Vector3D directionOfLight = Scene::lights[i]->getLightDirection(intersectionPosition);
        // /calculate shadows
        Ray shadowRay(intersectionPosition, directionOfLight);
        for (int j = 0; j < Scene::shapes.size(); j++){
            if (j == indexOfIntersectionPosition) continue;                             // Ignore what happens later because we do not want the shape to cast shadow onto itself
            double t = Scene::shapes[j]->rayIntersectionDistance(shadowRay);
            if (t > 0.000001 && distanceBetweenLightAndObject >= t){
                isShadowed = true;
                break;
            }
            isShadowed = false;
        }
        if (isShadowed) continue;                                   // Check if the other light falls on the currently shadowed reason
                                                                    // , in which case I'd not want a shadow
        float diffuseReflectance = 1 - Scene::shapes[indexOfIntersectionPosition]->getAmbience();
        Vector3D normalAtIntersectionPosition = Scene::shapes[indexOfIntersectionPosition]->getInverseTransformationMatrix() * Scene::shapes[indexOfIntersectionPosition]->getNormalAt(intersectionPosition);
        ColorRGB colorOfCurrentLight = Scene::lights[i]->getColorOfLight();
        double intensityOfCurrentLight = Scene::lights[i]->getLightIntensity();
        double cosineAngle = DotProduct(normalAtIntersectionPosition, directionOfLight);
        if (cosineAngle < 0) cosineAngle = 0;
        double factor = diffuseReflectance * intensityOfCurrentLight * cosineAngle;
        finalColor = finalColor + (factor * colorOfObject * colorOfCurrentLight);
    }
    return  finalColor + Scene::shapes[indexOfIntersectionPosition]->getAmbience() * colorOfObject;
}


Vector3D Camera::inverseTransformPoint(const Vector3D &point, int shapeIndex) {
    return Scene::shapes[shapeIndex]->getInverseTransformationMatrix() * point;
}

Vector3D Camera::inverseTransformDirection(const Vector3D &direction, int shapeIndex) {
    return Scene::shapes[shapeIndex]->getInverseTransformationMatrix() * direction;
}


Vector3D Camera::getCameraPosition() {
    return position;
}


void Camera::useSampling(SamplingTypes typeOfSampling, int numberOfSamples) {
    this->typeOfSampling = typeOfSampling;
    this->numberOfSamples = numberOfSamples;
}


void Camera::useDepthOfField(double apertureSize, const Vector3D& focalPoint) {
    this->apertureRadius = apertureSize;
    this->focalLength = (focalPoint - getCameraPosition()).magnitude();
    this->depthOfFieldEnabled = true;
}

Vector3D Camera::randomizeOriginXY() {
    // Use polar coordinates to convert from (radius, angle) to cartesian coordinates
    const float PI = 3.1415926535f;
    double cosineOfRandomAngle = cos(Algebra::getRandomBetween(0, 2 * PI));
    double sineOfRandomAngle = sin(Algebra::getRandomBetween(0, 2 * PI));
    double randomRadius = Algebra::getRandomBetween(0, apertureRadius);

    double xComponent = randomRadius * cosineOfRandomAngle;
    double yComponent = randomRadius * sineOfRandomAngle;
    return Vector3D(xComponent, yComponent, 0);
}