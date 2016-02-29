//
// Created by Sashank on 2/28/2016.
//

#ifndef ADVANCEDSCRIPTING2_IMAGEOUTPUT_H
#define ADVANCEDSCRIPTING2_IMAGEOUTPUT_H


#include <stdint.h>

class ImageOutput {
public:
    static void draw(int width, int height,uint8_t colors[4],const char* filename);
};


#endif //ADVANCEDSCRIPTING2_IMAGEOUTPUT_H
