#include <iostream>
#include "Scene/Scene.h"
#include "Shapes/Plane/Plane.h"
#include "Shapes/Box/Box.h"
#include "Shapes/Disk/Disk.h"
#include <ctime>

using namespace std;
void initializeObjects();
void initializeLights();

/*
 * TO DO
 * Replace all string params with enumerations
 */

int main() {
    //Random seed
    srand((unsigned  int)time(NULL));
    clock_t start = clock();
    cout << "Rendering scene..." << endl;
    cout << "Please wait." << endl;
    initializeObjects();
    initializeLights();
    Camera myCamera(Vector3D(10,30,-55), Vector3D(0,0,0), 72);              //First argument is the position of the camera, second is look at point
    myCamera.useSampling(SamplingTypes::JITTERED, 4);
    myCamera.render(600,600);

    cout << "Done rendering " << Scene::shapes.size() << " objects." <<endl;
    double duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cout << "Total time taken: " << duration << " seconds." << endl;
    return 0;
}

void initializeObjects(){
    //Plane
    Scene::shapes.push_back(std::make_shared<Plane>(Vector3D(0,1,0), Vector3D(0,-2,0),COLOR_GRAY, 0.3));

    //Sphere
    Scene::shapes.push_back(std::make_shared<Sphere>(8, Vector3D(-15,8,-10), COLOR_RED, 0.08));
    Scene::shapes.push_back(std::make_shared<Sphere>(7, Vector3D(35,10,30), COLOR_GREEN, 0.13));
    //Scene::shapes.push_back(std::make_shared<Sphere>(1, Vector3D(-9,0,0), COLOR_GREEN, 0.1));

    //Boxes
    Scene::shapes.push_back(std::make_shared<Box>(Vector3D(-25,15,10), Vector3D(-15,20,15), COLOR_RED, 0.3));

    //Disk
    Scene::shapes.push_back(std::make_shared<Disk>(Vector3D(0.12,1,0.12),Vector3D(10,2,-8), 4, ColorRGB(0.8,0.2,0.7,0.5), 0.1));
}

void initializeLights(){
    //Add one light of white color
    //Scene::lights.push_back(std::make_shared<Light>(TypesOfLight::DIRECTIONALLIGHT, Vector3D(1,500,0.25), 0.9, COLOR_WHITE));
    Scene::lights.push_back(std::make_shared<Light>(TypesOfLight::POINTLIGHT, Vector3D(100,60,-10), ColorRGB(1,1,0,1)));
    Scene::lights.push_back(std::make_shared<Light>(TypesOfLight::POINTLIGHT, Vector3D(-20,30,2), 0.6, ColorRGB(1,1,1,1)));
}