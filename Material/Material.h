//
// Created by Sashank on 5/24/2016.
//

#ifndef RAYTRACERC_MATERIAL_H
#define RAYTRACERC_MATERIAL_H


class Material{
private:
    float ambience;
    float specularPower;
    float specularCoeff;
    float diffuseCoeff;
    float reflectivity;
    ColorRGB color;
public:
    bool isReflective;
    Material(){
        this->specularCoeff = 0.4;
        this->diffuseCoeff = 0.4;
        this->ambience = 0.1;
        this->specularPower = 50;
        this->reflectivity = 0.1;
        this->color = ColorRGB(0,0,0,0);
        this->isReflective = false;
    }

    Material(ColorRGB color, float ambience, float reflectivity) {
        this->specularCoeff = 0.4;
        this->diffuseCoeff = 0.4;
        this->specularPower = 50;
        this->reflectivity = reflectivity;
        this->ambience = ambience;
        this->color = color;
    }


    float getAmbience() const {
        return ambience;
    }


    void setAmbience(const float ambience){
        this->ambience = ambience;
    }

    float getSpecularPower() const {
        return specularPower;
    }

    void setSpecularPower(const float specularPower) {
        this->specularPower = specularPower;
    }

    float getDiffuseCoefficient() const {
        return diffuseCoeff;
    }

    void setDiffuseCoeff(const float diffuseReflectance) {
        this->diffuseCoeff = diffuseReflectance;
    }

    const ColorRGB getColor() const{
        return color;
    }

    void setColor(const ColorRGB & color){
        this->color = color;
    }

    const void setReflectivity(const float intensity){
        this->reflectivity = intensity;
    }

    const float getReflectivity() const{
        return reflectivity;
    }


    float getSpecularCoeff() const {
        return specularCoeff;
    }

    void setSpecularCoeff(float specularCoeff) {
        this->specularCoeff = specularCoeff;
    }

    virtual ColorRGB getColorAtPoint(const Vector3D & point){
        return color;
    }
};


#endif //RAYTRACERC_MATERIAL_H
