//
// Created by Sashank on 3/9/2016.
//

#ifndef RAYTRACERC_LIGHT_H
#define RAYTRACERC_LIGHT_H

#include "../Vector3D/Vector3D.h"
#include "../Color/Color.h"
#include "../Scene/Scene.h"


using namespace Vector;
enum TypesOfLight{
    DIRECTIONALLIGHT,
    POINTLIGHT
};
class Light{
private:
    Vector3D lightPosition;
    ColorRGB colorOfLight;
    Vector3D lightDirection;
    TypesOfLight typeOfLight;
    double intensityOfLight;
public:

    //Constructors

    Light(TypesOfLight _typeOfLight, Vector3D lightPosition_Direction){
        this->typeOfLight = _typeOfLight;
        if (typeOfLight == TypesOfLight::POINTLIGHT) {
            this->lightPosition = lightPosition_Direction;
        } else if (typeOfLight == TypesOfLight::DIRECTIONALLIGHT){
            this->lightDirection = lightPosition_Direction.unitVector();
        }
        this->colorOfLight = ColorRGB(1,1,1,1);
        this->intensityOfLight = 0.5;
    };

    Light(TypesOfLight _typeOfLight, Vector3D lightPosition_Direction, double lightIntensity):
            Light(_typeOfLight, lightPosition_Direction){
        this->intensityOfLight = lightIntensity;
    }

    Light(TypesOfLight _typeOfLight, Vector3D lightPosition_Direction, ColorRGB colorOfLight):
            Light(_typeOfLight, lightPosition_Direction){
        this->colorOfLight = colorOfLight;
        this->intensityOfLight = 0.5;
    };

    Light(TypesOfLight _typeOfLight, Vector3D lightPosition_Direction, double lightIntensity, ColorRGB colorOfLight)
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
        if (typeOfLight == TypesOfLight::POINTLIGHT){
            return (getLightPosition() - point).unitVector();
        } else {
            return lightDirection;
        }
    }

    virtual double getLightIntensity(){
        return intensityOfLight;
    }

    virtual TypesOfLight getLightType(){
        return typeOfLight;
    }
};
#endif //RAYTRACERC_LIGHT_H
