//
// Created by Sashank on 3/2/2016.
//
#ifndef IMAGEOUTPUTCLASS_COLOR_H
#define IMAGEOUTPUTCLASS_COLOR_H


#include <stdint-gcc.h>

class Colour {
private:
    float rgba[4];
public:
    Colour(float _red, float _green, float _blue, float _alpha=1.0):
            rgba{_red, _green, _blue, _alpha} {};
    Colour():
            rgba{1.0,1.0,1.0,1.0} {};

    const float getRed();
    const float getGreen();
    const float getBlue();
    const float getAlpha();

    const uint8_t getRedInt();
    const uint8_t getGreenInt();
    const uint8_t getBlueInt();
    const uint8_t getAlphaInt();

    uint8_t * convertToUint8();

};


#endif //IMAGEOUTPUTCLASS_COLOR_H
