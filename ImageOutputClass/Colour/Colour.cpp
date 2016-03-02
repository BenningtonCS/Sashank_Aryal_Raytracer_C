//
// Created by Sashank on 3/2/2016.
//

#include <math.h>
#include <cmath>
#include "Colour.h"

uint8_t*Colour::convertToUint8() {
    uint8_t convertedColor[] = {
            getRedInt(),
            getGreenInt(),
            getBlueInt(),
            getAlphaInt()
    };
    return convertedColor;
}

const float Colour::getRed() {
    return this->rgba[0];
}

const float Colour::getGreen() {
    return this->rgba[1];
}

const float Colour::getBlue() {
    return this->rgba[2];
}

const float Colour::getAlpha() {
    return this->rgba[3];
}

const uint8_t Colour::getRedInt() {
    return (uint8_t)(floor(pow(this->rgba[0],(1/2.2))*255));
}

const uint8_t Colour::getGreenInt() {
    return (uint8_t)(floor(pow(this->rgba[1],(1/2.2))*255));
}

const uint8_t Colour::getBlueInt() {
    return (uint8_t)(floor(pow(this->rgba[2],(1/2.2))*255));
}

const uint8_t Colour::getAlphaInt() {
    return (uint8_t)(floor(pow(this->rgba[3],(1/2.2))*255));
}
