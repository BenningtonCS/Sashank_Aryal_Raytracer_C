//
// Created by Sashank on 3/9/2016.
//

#ifndef RAYTRACERC_LIGHT_H
#define RAYTRACERC_LIGHT_H

#include "../Vector3D/Vector3D.h"
#include "../Color/Color.h"
#include "../Scene/Scene.h"

using namespace Vector;

/*
 * Three different types of lighting
 * 1. Diffuse
 * 2. Specular -> an object is really smooth, where there is one bright spot of light reflection (very natural) example- screen, tables
 * 3. Ambient -> LIght which bounces off anything
 *
 *
 * Diffuse:
 * Sources:
 * 1. Directional Light
 *              --> Rays are practically "parallel". Particularly good for simulating sun. NO POSITION (usually)
 *              --> Associated properties:
 *                      - Vector3D Direction
 *                      - ~ Color
 *              --> Intersection point (p), Center of sphere (c)
 *              --> Normal (perpendicular to the tangent at the point)
 *                  - Easy for sphere. UnitVector ( p - c )
 *              --> If the normal is pointing towards the light, it will be lit, otherwise not.
 *              --> USe dotProdcut to find the light intensity - ( Directionofligth, normalvector of sphere)
 *
 * 2. Point Light
 *              --> Has a position ( l )
 *              --> d = p - l
 *
 * Ambient light:
 *          --> Will lit TOTALLY dark places
 *          --> No location and direction
 *          --> Will affect the intensity, if too big, image will be very saturated
 *          --> Can even be an intrinsic property of material. It's like saying an object will not get any darker than
 *          a threshold value - OPTION 1
 *          --> Set it as a light source with direction 1
 */
class Light{
private:
    Vector3D lightPosition;
    ColorRGB colorOfLight;
    Vector3D lightDirection;
    const char* typeOfLight;
    double intensityOfLight;
public:

    //Constructors

    Light(const char* _typeOfLight, Vector3D lightPosition_Direction){
        this->typeOfLight = _typeOfLight;
        if (typeOfLight == "point") {
            this->lightPosition = lightPosition_Direction;
        } else if (typeOfLight == "direction"){
            this->lightDirection = lightPosition_Direction.unitVector();
        }
        this->colorOfLight = ColorRGB(1,1,1,1);
        this->intensityOfLight = 0.5;
    };

    Light(const char* _typeOfLight, Vector3D lightPosition_Direction, double lightIntensity):
            Light(_typeOfLight, lightPosition_Direction){
        this->intensityOfLight = lightIntensity;
    }

    Light(const char* _typeOfLight, Vector3D lightPosition_Direction, ColorRGB colorOfLight):
            Light(_typeOfLight, lightPosition_Direction){
        this->colorOfLight = colorOfLight;
        this->intensityOfLight = 0.5;
    };

    Light(const char* _typeOfLight, Vector3D lightPosition_Direction, double lightIntensity, ColorRGB colorOfLight)
    :Light(_typeOfLight, lightPosition_Direction, lightIntensity){
        this->colorOfLight = colorOfLight;
        this->intensityOfLight = lightIntensity;
    }


    virtual Vector3D getLightPosition(){
        return lightPosition;
    };

    virtual ColorRGB getColorOfLight(){
        return colorOfLight;
    };

    virtual Vector3D getLightDirection(Vector3D point) {
        if (typeOfLight == "point"){
            return (getLightPosition() - point).unitVector();
        } else {
            return lightDirection;
        }
    }

    virtual double getLightIntensity(){
        return intensityOfLight;
    }
};
#endif //RAYTRACERC_LIGHT_H
