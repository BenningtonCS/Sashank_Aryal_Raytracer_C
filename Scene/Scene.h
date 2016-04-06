//
// Created by Sashank on 3/9/2016.
//

#ifndef RAYTRACERC_SCENE_H
#define RAYTRACERC_SCENE_H


//Macros definitions

#define COLOR_BLACK ColorRGB(0,0,0,0)
#define COLOR_RED ColorRGB(1,0,0,0)
#define COLOR_GRAY ColorRGB(0.5,0.5,0.5,0)
#define COLOR_WHITE ColorRGB(1,1,1,0)
#define COLOR_GREEN ColorRGB(0,1,0,1)
#define ORIGIN Vector3D(0,0,0)
#define TOPRIGHTCORNER Vector3D(30,30,0)
#define BACKGROUNDCOLOR ColorRGB(0,0,0,0)

#include "../Vector3D/Vector3D.h"
#include "../Camera/Camera.h"
#include "../Lights/Light.h"
#include "../Shapes/Sphere/Sphere.h"
#include <vector>
#include <memory>

class Scene{
private:

public:
    //Constructor
    Scene();

    static std::vector<std::shared_ptr<Shape>> shapes;
    static std::vector<std::shared_ptr<Light>> lights;
};


#endif //RAYTRACERC_SCENE_H
