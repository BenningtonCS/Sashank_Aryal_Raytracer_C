//
// Created by Sashank on 3/8/2016.
//

#ifndef RAYTRACERC_IMAGE_H
#define RAYTRACERC_IMAGE_H


#include "../Color/Color.h"

class CreateImage {
private:
    //Constructor made public so that the class can never be instantiated
    CreateImage(){};
public:
    static void createRasterImage(int height, int width, const char* fileName, ColorRGB* colors);
};


#endif //RAYTRACERC_IMAGE_H
