//
// Created by Sashank on 3/9/2016.
//
#pragma once
#ifndef RAYTRACERC_SCENE_H
#define RAYTRACERC_SCENE_H

#include "../Vector3D/Vector3D.h"
#include "../Camera/Camera.h"
#include "../Shapes/Sphere/Sphere.h"

#include <memory>
#include <vector>

class Scene{
private:
    Camera camera;
    int height, width;
public:
    //Constructor
    Scene();
    Scene(const Camera & camera);
    std::vector<std::shared_ptr<Shape>> shapes;
    std::vector<std::shared_ptr<Light>> lights;

    void setCamera(const Camera & camera);
    void setSize(int width, int height);
    void render();
};


#endif //RAYTRACERC_SCENE_H
