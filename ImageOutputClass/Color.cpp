//
// Created by Sashank on 3/2/2016.
//

#include <math.h>
#include "Color.h"

uint8_t* Color::convertToUint8() {
    uint8_t convertedColor[] = {
            (uint8_t) (floor(this->rgba[0] * 255)),
            (uint8_t) (floor(this->rgba[1] * 255)),
            (uint8_t) (floor(this->rgba[2] * 255)),
            (uint8_t) (floor(this->rgba[3] * 255))
    };
    return convertedColor;
}