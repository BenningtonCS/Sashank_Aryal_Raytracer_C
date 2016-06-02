    //
// Created by Sashank on 3/9/2016.
//

#include <iostream>
#include "Scene.h"
#include <algorithm>

using namespace Vector;

//Constructor method
Scene::Scene() {
        this->camera = Camera(Vector3D(0,0,-300), Vector3D());
}
Scene::Scene(const Camera & camera){
    this->camera = camera;
}

void Scene::setCamera(const Camera & camera){
    this->camera = camera;
}

void Scene::setSize(int width, int height){
    this->width = width;
    this->height = height;
}
void Scene::render(){
    camera.render(width, height, shapes, lights);
}