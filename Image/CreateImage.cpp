//
// Created by Sashank on 3/8/2016.
//

#include "CreateImage.h"
#include "../EasyBMP/EasyBMP.h"

void CreateImage::createRasterImage(int height, int width, const char *fileName, ColorRGB* colors) {
    BMP myImage;
    myImage.SetSize(width, height);
    myImage.SetBitDepth(32);
    int loopCounter = 0;
    for (int i=0; i<width; ++i) {
        for (int j = 0; j < height; ++j) {
            ++loopCounter;
            ColorRGB rgb = colors[loopCounter];
            myImage.operator()(i,j)->Red = rgb.getRedInt();
            myImage.operator()(i,j)-> Green= rgb.getGreenInt();
            myImage.operator()(i,j)-> Blue = rgb.getBlueInt();
            myImage.operator()(i,j)->Alpha = rgb.getAlphaInt();
        }
    }
    myImage.WriteToFile(fileName);
}