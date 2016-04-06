//
// Created by Sashank on 3/8/2016.
//

#ifndef RAYTRACERC_RAY_H
#define RAYTRACERC_RAY_H
#include "../Vector3D/Vector3D.h"
using namespace Vector;
class Ray{
private:
    Vector3D origin, direction;

public:
    //Constructors

    Ray(const Vector3D &origin, const Vector3D &direction)
            : origin(origin),
              direction(direction)
    {}

    Ray (){
        origin = Vector3D(0,0,0);
        direction = Vector3D(1,0,0);
    }

    //Destructor
    ~Ray () {

    }


    //Getters

    const Vector3D &getOrigin() const {
        return origin;
    }

    const Vector3D &getDirection() const {
        return direction;
    }
};
#endif //RAYTRACERC_RAY_H
