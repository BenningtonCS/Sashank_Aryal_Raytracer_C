#include <iostream>
#include "Scene/Scene.h"
#include "Shapes/Plane/Plane.h"
#include "Shapes/Box/Box.h"

using namespace std;
const Vector3D getRandomPositionBetween(const Vector3D & initial, const Vector3D & final);
const ColorRGB getRandomColor();
const Material getRandomMaterial();

/*
 * TO DO
 * Replace all string params with enumerations
 */

int main() {
    //Random seed
    srand((unsigned  int)time(NULL));
    clock_t start = clock();

    
    // TEST SCENE
    Scene testScene;
    testScene.setSize(600, 600);
    Camera cameraTest(Vector3D(0,20,-200), Vector3D(0,0,0), 52);              //First argument is the position of the camera, second is look at point
    cameraTest.useSampling(SamplingTypes::RANDOM, 1);
    //Objects
    auto testSphere =  make_shared<Sphere>();
    testSphere->setPosition(Vector3D(-30,-20,-20));
    testSphere->setRadius(20);
    testSphere->setMaterial(getRandomMaterial());
    testSphere->scaleMatrixXYZBy(Vector3D(2,1,1));
    testSphere->rotateAround_Z_By(45);
    testScene.shapes.emplace_back(testSphere);
    //Lights
    testScene.lights.emplace_back(std::make_shared<Light>(TypesOfLight::POINTLIGHT, Vector3D(80,300,-140), ColorRGB(0.9,1,1,1)));
    //testScene.render();


    // SCENE ONE
    Scene scene1;
    scene1.setSize(600, 600);
    Camera camera(Vector3D(0,0,-299), Vector3D(0,0,0), 52);              //First argument is the position of the camera, second is look at point
    camera.useSampling(SamplingTypes::RANDOM, 10);
    camera.setMaxDepth(10);
    //myCamera.useDepthOfField(2, Vector3D(10,5.5,0));
    scene1.setCamera(camera);

    //Objects for scene1
    auto sphere1 = make_shared<Sphere>();
    sphere1->setPosition(Vector3D(-30,-20,-20));
    sphere1->setRadius(20);
    sphere1->setMaterial(getRandomMaterial());

    auto sphere2 = make_shared<Sphere>();
    sphere2->setPosition(Vector3D(20,20,0));
    sphere2->setRadius(20);
    sphere2->setMaterial(getRandomMaterial());

    auto sphere3 = make_shared<Sphere>();
    sphere3->setPosition(Vector3D(20,-25,-25));
    sphere3->setRadius(20);
    sphere3->setMaterial(getRandomMaterial());

    auto sphere4 = make_shared<Sphere>();
    sphere4->setPosition(Vector3D(-30,20,-4));
    sphere4->setRadius(20);
    Material sphere4Material;
    sphere4Material.setAmbience(0);
    sphere4Material.setDiffuseCoeff(0);
    sphere4Material.setSpecularCoeff(0);
    sphere4Material.setColor(ColorRGB(1,1,1,1));
    sphere4Material.setReflectivity(1);
    sphere4Material.isReflective = true;
    sphere4->setMaterial(sphere4Material);

    auto plane1 = make_shared<Plane>();
    plane1->setNormalOrientationVector(Vector3D(0,0,1));
    plane1->setPointOnPlane(Vector3D(0,0,30));
    Material plane1Material;
    plane1Material.setAmbience(0.1);
    plane1Material.setDiffuseCoeff(0.4);
    plane1Material.setSpecularCoeff(0.3);
    plane1Material.setColor(ColorRGB(1,0.5,1,1));
    plane1Material.setReflectivity(0.2);
    plane1->setMaterial(plane1Material);

    scene1.shapes.insert(scene1.shapes.end(), {sphere1});

    //Lights for scene1
    scene1.lights.emplace_back(std::make_shared<Light>(TypesOfLight::POINTLIGHT, Vector3D(-80,200,-500), ColorRGB(1,1,1,1)));
    scene1.lights.emplace_back(std::make_shared<Light>(TypesOfLight::POINTLIGHT, Vector3D(80,200,-140), ColorRGB(0.9,1,1,1)));

    scene1.render();





    // SCENE TWO
    Scene scene2;
    scene2.setSize(1200, 1200);
    Camera camera2(Vector3D(0,20,-800), Vector3D(0,0,0), 52);              //First argument is the position of the camera, second is look at point
    camera2.useSampling(SamplingTypes::RANDOM, 30);
    //myCamera.useDepthOfField(2, Vector3D(10,5.5,0));
    scene2.setCamera(camera2);

    //Lights for scene1
    scene2.lights.emplace_back(std::make_shared<Light>(TypesOfLight::POINTLIGHT, Vector3D(-80,300,-150), ColorRGB(1,1,1,1)));
    scene2.lights.emplace_back(std::make_shared<Light>(TypesOfLight::POINTLIGHT, Vector3D(80,300,-140), ColorRGB(0.9,1,1,1)));

    //Objects for scene2
    int numberOfSpheres = 35;
    Vector3D minimumVector = Vector3D(-250, -300, -400);
    Vector3D maximumVector = Vector3D(250, 300, 50);

    //Sphere
    for (int i = 0; i < numberOfSpheres; i++){
        auto sphere = make_shared<Sphere>();
        sphere->setPosition(getRandomPositionBetween(minimumVector, maximumVector));
        sphere->setRadius(Algebra::getRandomBetween(10, 40));
        sphere->setMaterial(getRandomMaterial());
        scene2.shapes.emplace_back(sphere);
    }

    //scene2.render();

    double duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cout << "Total time taken: " << duration << " seconds." << endl;
    return 0;
}

const Vector3D getRandomPositionBetween(const Vector3D & initial, const Vector3D & final){
    double x = Algebra::getRandomBetween(initial.getX(), final.getX());
    double y = Algebra::getRandomBetween(initial.getY(), final.getY());
    double z = Algebra::getRandomBetween(initial.getZ(), final.getZ());
    return Vector3D(x, y, z);
}

const ColorRGB getRandomColor(){
    double r = Algebra::getRandomBetween(0, 1);
    double g = Algebra::getRandomBetween(0, 1);
    double b = Algebra::getRandomBetween(0, 1);
    double a = 1;
    return ColorRGB(r, g, b, a);
}

const Material getRandomMaterial(){
    Material material;
    material.setAmbience((float)Algebra::getRandomBetween(0.05, 0.1));
    material.setColor(getRandomColor());
    material.setReflectivity((float)Algebra::getRandomBetween(0.1, 0.2));
    material.setSpecularCoeff((float)Algebra::getRandomBetween(0.2, 0.3));
    material.setSpecularPower((int)Algebra::getRandomBetween(20,50));
    material.setDiffuseCoeff(0.4);
    material.setSpecularPower((int)Algebra::getRandomBetween(49, 50));
    return material;
}