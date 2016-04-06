//
// Created by Sashank on 3/9/2016.
//

#include <iostream>
#include "Scene.h"
#include <map>
#include <algorithm>

using namespace Vector;

//Constructor method
Scene::Scene() {
}
/*
Scene::Scene(Vector3D cameraPosition) {

}

Scene::Scene(Vector3D cameraPosition, Light sceneLight) {
    initializeCamera(cameraPosition);
    initializeLight(sceneLight);
}


//This method initializes the camera
Camera Scene::initializePerspectiveCamera(Vector3D cameraPosition) {
    // Definition of the 3D coordinate space
    Vector3D coordinates[3];
    coordinates[0] = Vector3D(1,0,0);       //Basis vector x
    coordinates[1] = Vector3D(0,1,0);       //Basis vector y
    coordinates[2] = Vector3D(0,0,1);       //Basis vector z
    Vector3D lookAtPoint(0,0,0);                //The point we want our camera to look at
    Vector3D differenceBetweenImageAndCamera = cameraPosition - lookAtPoint;       //The difference between the camera and the point where we want to look
    Vector3D cameraDirection = -differenceBetweenImageAndCamera.unitVector();       //Normalize the difference and make it positive by multiplying with -1
    // CREATE A VIRTUAL COORDINATE SYSTEM FOR THE CAMERA
    Vector3D cameraRightLeft = CrossProduct(coordinates[1],cameraDirection).unitVector();
    Vector3D cameraUpDown = CrossProduct(cameraDirection, cameraRightLeft);
    Camera myCamera(cameraPosition, cameraDirection, cameraRightLeft, cameraUpDown);
    return myCamera;
}
*/
// This method initializes the orthographic camera.

//This method initializes the light source.




std::vector<std::shared_ptr<Shape>> Scene::shapes;              // Definition of the shapes container
std::vector<std::shared_ptr<Light>> Scene::lights;              // Definition of the lights container