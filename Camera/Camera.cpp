//
// Created by Sashank on 3/26/2016.
//

#include "Camera.h"
#include "../Scene/Scene.h"
#include "../Image/CreateImage.h"
#include "../Algebra/Algebra.h"

Camera::Camera(const Vector3D &position, const Vector3D &lookAtPoint) {
    this->position = position;

    Vector3D differenceBetweenImageAndCamera = lookAtPoint - position;       //The difference between the camera and the point where we want to look

    // CREATE A VIRTUAL COORDINATE SYSTEM FOR THE CAMERA. IN ORTHONORMAL BASIS
    w = differenceBetweenImageAndCamera.unitVector();       //Normalize the difference and make it positive by multiplying with -1
    u = CrossProduct(Vector3D(0,1,0),w).unitVector();
    v = CrossProduct(w, u);
    fov = 52.0;
}

Vector3D Camera::convertCameraToWorldCoordinates(Vector3D point) {
    return ((point.getX() * u + (point.getY() * v) + (point.getZ() * w)));
}

Camera::Camera(const Vector3D &position, const Vector3D &lookAtPoint, double fov):
    Camera(position, lookAtPoint)
{
    this->fov = fov;
}



void Camera::render(const int width, const int height){
    int numberOfObjectsToRender = Scene::shapes.size();

    int resolution = width * height;
    double scale = tan(Algebra::deg2rad(fov * 0.5));  //deg to rad
    ColorRGB *pixels = new ColorRGB[resolution];

    int loopCounter = 0;

    Vector3D camRayOrigin = getCameraPosition();
    Vector3D camRayDirection;

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            double xCamDir = (i - (width / 2)) + 0.5;
            double yCamDir = ((height / 2) - j) + 0.5;
            double zCamDir = (height/2) / scale;
            camRayDirection = convertCameraToWorldCoordinates(Vector3D(xCamDir, yCamDir, zCamDir)).unitVector();
            Ray r(camRayOrigin, camRayDirection);
            loopCounter++;
            // Render all objects that are inside the shape container
            // If more than one object is hit, the one with the intersection point closer to the observer commands the pixel color,
            int lowestTposition = 0;
            double leastValueOfT = 100000000;
            Vector3D intersecting_position;
            for (int k = 0; k < numberOfObjectsToRender; ++k) {
                double intersectionDistance = Scene::shapes[k]->rayIntersectionDistance(r);
                if (intersectionDistance > 0.000001 && intersectionDistance < leastValueOfT) {  //0.000001 for accuracy purpose
                    leastValueOfT = intersectionDistance;
                    lowestTposition = k;
                    intersecting_position = camRayOrigin + leastValueOfT * camRayDirection;
                    //Compute shadows
                }
            }
            if (leastValueOfT < 100000) {
                pixels[loopCounter - 1] = getColorAt(intersecting_position, lowestTposition);
            } else {
                pixels[loopCounter - 1] = BACKGROUNDCOLOR;
            }
        }
    }
    CreateImage::createRasterImage(height, width, "RenderedImage.bmp", pixels);
    delete pixels;      //Release memory
}


ColorRGB Camera::getColorAt(Vector3D intersectionPosition, int lowestTPosition) {
    float diffuseReflectance = 1 - Scene::shapes[lowestTPosition]->getAmbience();
    ColorRGB colorOfObject = Scene::shapes[lowestTPosition]->getColor();
    Vector3D normalAtIntersectionPosition = Scene::shapes[lowestTPosition]->getNormalAt(intersectionPosition);
    ColorRGB finalColor(0,0,0,0);
    bool isShadowed = false;
    for (int i = 0; i < Scene::lights.size(); i++) {
        ColorRGB colorOfCurrentLight = Scene::lights[i]->getColorOfLight();
        double intensityOfCurrentLight = Scene::lights[i]->getLightIntensity();
        Vector3D directionOfLight = Scene::lights[i]->getLightDirection(intersectionPosition);

        //calculate shadows
        Ray shadowRay(intersectionPosition, directionOfLight);
        double leastValueOfT = 10000000;
        for (int j = 0; j < Scene::shapes.size() && !isShadowed; j++){
            if (j == lowestTPosition) continue;                             // Ignore what happens later because we do not want the shape to cast shadow onto itself
            double t = Scene::shapes[j]->rayIntersectionDistance(shadowRay);
            if (t < leastValueOfT && t > 0){
                leastValueOfT = t;
                isShadowed = true;
            }
        }
        if (leastValueOfT < 10000000) {
            finalColor = Scene::shapes[lowestTPosition]->getAmbience() * colorOfObject;
            return finalColor;
        }

        if (!isShadowed) {
            double cosineAngle = DotProduct(normalAtIntersectionPosition, directionOfLight);
            if (cosineAngle < 0) cosineAngle = 0;
            double factor = diffuseReflectance * intensityOfCurrentLight * cosineAngle;
            finalColor = finalColor + (factor * colorOfObject * colorOfCurrentLight);
        }
    }
    return  finalColor + Scene::shapes[lowestTPosition]->getAmbience() * colorOfObject;
}

Vector3D Camera::getCameraPosition() {
    return position;
}



