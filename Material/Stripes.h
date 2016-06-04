//
// Created by Sashank on 6/3/2016.
//

#ifndef RAYTRACERC_STRIPES_H
#define RAYTRACERC_STRIPES_H

#include "../Color/Color.h"
#include "../Vector3D/Vector3D.h"
#include "Material.h"

class Stripes: public Material{
public:
    ColorRGB color2;

    Stripes(const ColorRGB & color1, const ColorRGB & color2){
        this->color2 = color2;
        Material::setColor(color1);
    }

    ColorRGB getColorAtPoint(const Vector::Vector3D & point){
        if ((cos(point.getZ()) > 0.5 && sin(point.getY()) > 0.5 ) || (sin(point.getZ()) < -0.3 && sin(point.getX()) < -0.3))
        {
            return color2;
        }
        else if ((sin(point.getZ()) > 0 && sin(point.getX()) > 0) || (sin(point.getZ()) < 0 && sin(point.getX()) < 0))
        {
            return ColorRGB(1,0,0,1);
        }
        else
        {
            return Material::getColor();
        }
    }
};
#endif //RAYTRACERC_STRIPES_H
