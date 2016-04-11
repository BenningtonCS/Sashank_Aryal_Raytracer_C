//
// Created by Sashank on 3/9/2016.
//

#include <iostream>
#include "Scene.h"
#include <algorithm>

using namespace Vector;

//Constructor method
Scene::Scene() {
}

std::vector<std::shared_ptr<Shape>> Scene::shapes;              // Definition of the shapes container
std::vector<std::shared_ptr<Light>> Scene::lights;              // Definition of the lights container