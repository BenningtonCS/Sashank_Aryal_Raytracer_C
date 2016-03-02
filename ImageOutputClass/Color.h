//
// Created by Sashank on 3/2/2016.
//
#ifndef IMAGEOUTPUTCLASS_COLOR_H
#define IMAGEOUTPUTCLASS_COLOR_H


#include <stdint-gcc.h>

class Color {
private:
    float rgba[4];
public:
    Color(float _red, float _green, float _blue, float _alpha=1.0):
            rgba{_red, _green, _blue, _alpha} {};
    uint8_t * convertToUint8();

};


#endif //IMAGEOUTPUTCLASS_COLOR_H
