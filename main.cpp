#include <iostream>
#include "Scene/Scene.h"
#include "Shapes/Plane/Plane.h"
#include "Shapes/Box/Box.h"
#include "Shapes/Disk/Disk.h"
#include "Algebra/Matrix.h"
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


    Camera myCamera(Vector3D(10,33,-80), Vector3D(0,0,0), 51);              //First argument is the position of the camera, second is look at point
    myCamera.useSampling(SamplingTypes::JITTERED, 2);
    //myCamera.useDepthOfField(20, Vector3D(10,5.5,0));
    myCamera.render(600, 600);

    cout << "Done rendering " << Scene::shapes.size() << " objects." <<endl;
    double duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cout << "Total time taken: " << duration << " seconds." << endl;
    return 0;
}

void initializeObjects(){
    //Plane
    auto mainPlane = make_shared<Plane>(Vector3D(0,1,0), Vector3D(0,-3,0),COLOR_GRAY, 0.3);
    //mainPlane->scaleMatrixXYZBy(Vector3D(2,2,2));
    Scene::shapes.emplace_back(mainPlane);

    //Sphere
    auto sphere1 = make_shared<Sphere>(6, Vector3D(0,3,-30), COLOR_RED, 0.08);
    sphere1->scaleMatrixXYZBy(Vector3D(2,2,1));
    Scene::shapes.emplace_back(sphere1);
    Scene::shapes.emplace_back(std::make_shared<Sphere>(3, Vector3D(15,0,-25), COLOR_GREEN, 0.1));

    //Boxes
    Scene::shapes.emplace_back(std::make_shared<Box>(Vector3D(-25,15,10), Vector3D(-15,20,15), COLOR_RED, 0.3));

    //Disk
    Scene::shapes.emplace_back(std::make_shared<Disk>(Vector3D(0,0,-1),Vector3D(10,5.5,0), 8, ColorRGB(0.94,0.5,0.5,0.5), 0.1));
}

void initializeLights(){
    //Add one light of white color
    //Scene::lights.emplace_back(std::make_shared<Light>(TypesOfLight::DIRECTIONALLIGHT, Vector3D(1,500,0.25), 0.9, COLOR_WHITE));
    Scene::lights.emplace_back(std::make_shared<Light>(TypesOfLight::POINTLIGHT, Vector3D(100,60,-10), ColorRGB(1,1,0,1)));
    Scene::lights.emplace_back(std::make_shared<Light>(TypesOfLight::POINTLIGHT, Vector3D(-20,30,2), 0.6, ColorRGB(1,1,1,1)));
}