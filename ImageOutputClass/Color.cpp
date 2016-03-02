//
// Created by Sashank on 3/2/2016.
//

#include <math.h>
#include <cmath>
#include "Color.h"

uint8_t* Color::convertToUint8() {
    uint8_t convertedColor[] = {
            getRedInt(),
            getGreenInt(),
            getBlueInt(),
            getAlphaInt()
    };
    return convertedColor;
}

const float Color::getRed() {
    return this->rgba[0];
}

const float Color::getGreen() {
    return this->rgba[1];
}

const float Color::getBlue() {
    return this->rgba[2];
}

const float Color::getAlpha() {
    return this->rgba[3];
}

const uint8_t Color::getRedInt() {
    return (uint8_t)(floor(pow(this->rgba[0],(1/2.2))*255));
}

const uint8_t Color::getGreenInt() {
    return (uint8_t)(floor(pow(this->rgba[1],(1/2.2))*255));
}

const uint8_t Color::getBlueInt() {
    return (uint8_t)(floor(pow(this->rgba[2],(1/2.2))*255));
}

const uint8_t Color::getAlphaInt() {
    return (uint8_t)(floor(pow(this->rgba[3],(1/2.2))*255));
}
