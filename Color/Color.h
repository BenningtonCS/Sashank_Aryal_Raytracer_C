//
// Created by Sashank on 3/8/2016.
//

#include <math.h>
#include <stdint.h>
#include <iostream>

#ifndef RAYTRACERC_COLOR_H
#define RAYTRACERC_COLOR_H



struct ColorRGB{
private:
    double r;
    double g;
    double b;
    double a;
public:

    //Constructor
    ColorRGB(const double r, const double g, const double b, const double a){
        this->r = r > 1 ? 1 : r;
        this->g = g > 1 ? 1 : g;
        this->b = b > 1 ? 1 : b;
        this->a = a > 1 ? 1 : a;
    }

    ColorRGB(){};

    ~ColorRGB(){

    }


    //Getters and setters
    const double getR() const {
        return r;
    }

    const double getG() const {
        return g;
    }

    const double getB() const {
        return b;
    }


    const double getA() const {
        return a;
    }


    const uint8_t getRedInt() const {
        return (uint8_t)(floor(pow(getR(),(1/2.2))*255));
    }

    const uint8_t getGreenInt() const {
        return (uint8_t)(floor(pow(getG(),(1/2.2))*255));
    }

    const uint8_t getBlueInt() const {
        return (uint8_t)(floor(pow(getB(),(1/2.2))*255));
    }

    const uint8_t getAlphaInt() const {
        return (uint8_t)(floor(getA()*255));
    }

};

inline ColorRGB operator+(const ColorRGB &c1, const ColorRGB &c2){
    return ColorRGB(c1.getR() + c2.getR(), c1.getG() + c2.getG(), c1.getB() + c2.getB(), c1.getA() + c2.getA());
}

inline ColorRGB operator*(const ColorRGB &c1, const ColorRGB &c2){
    return ColorRGB(c1.getR() * c2.getR(), c1.getG() * c2.getG(), c1.getB() * c2.getB(), c1.getA() * c2.getA());
}

inline ColorRGB operator*(const double s, const ColorRGB &c){
    return ColorRGB(s * c.getR(), s * c.getG(), s * c.getB(), s * c.getA());
}

inline ColorRGB operator/(const ColorRGB &c1, double constant){
    return ColorRGB(c1.getR() / constant, c1.getG() / constant, c1.getB() / constant, c1.getA());
}

inline ColorRGB operator+(double constant , const ColorRGB &c){
    return ColorRGB(constant + c.getR(), constant + c.getG(), constant + c.getB(), constant + c.getA());
}
#endif //RAYTRACERC_COLOR_H