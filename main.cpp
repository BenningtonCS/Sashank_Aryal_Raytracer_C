#include <iostream>
#include "Scene/Scene.h"
#include "Shapes/Plane/Plane.h"
#include "Shapes/Box/Box.h"
#include <ctime>

using namespace std;
void initializeObjects();
void initializeLights();

int main() {
    clock_t start = clock();
    cout << "Rendering scene..." << endl;
    cout << "Please wait." << endl;

    initializeObjects();
    initializeLights();
    Camera myCamera(Vector3D(100,40,-50), ORIGIN, 65);              //First argument is the position of the camera, second is look at point
    myCamera.render(800,900);

    cout << "Done rendering " << Scene::shapes.size() << " objects." <<endl;
    double duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cout << "Total time taken: " << duration << " seconds." << endl;
    return 0;
}

void initializeObjects(){
    //Plane
    Scene::shapes.push_back(std::make_shared<Plane>(Vector3D(0,1,0), Vector3D(0,-3,0),COLOR_GRAY, 0.3));

    //Disk

    //Sphere
    Scene::shapes.push_back(std::make_shared<Sphere>(10, Vector3D(60,20,-20), COLOR_RED, 0.08));
    Scene::shapes.push_back(std::make_shared<Sphere>(12, Vector3D(50,10,-40), COLOR_GREEN, 0.13));
    Scene::shapes.push_back(std::make_shared<Sphere>(3, Vector3D(-9,0,0), COLOR_GREEN, 0.1));

    //Boxes
    Scene::shapes.push_back(std::make_shared<Box>(Vector3D(-10,35,10), Vector3D(-30,45,20), COLOR_RED, 0.3));
}

void initializeLights(){
    //Add one light of white color
    Scene::lights.push_back(std::make_shared<Light>("point", Vector3D(110,100,0), COLOR_WHITE));
    Scene::lights.push_back(std::make_shared<Light>("point", Vector3D(20,100,-2), ColorRGB(1,1,1,1)));
}