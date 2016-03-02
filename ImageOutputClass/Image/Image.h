//
// Created by Sashank on 2/28/2016.
//

/*
 *
 * This class has two static methods.
 * 1. drawColoredBMP
 *      Description: It draws a 32 bit bitmap image of specified width and height and color.
 * 2. convertToGrayscale
 *      Description: It converts a bit map image to grayscale formal
  */
#ifndef ADVANCEDSCRIPTING2_IMAGEOUTPUT_H
#define ADVANCEDSCRIPTING2_IMAGEOUTPUT_H

#include <stdint.h>
#include "../Colour/Colour.h"

class Image {
public:
    static void drawColoredBMP(int width, int height, Colour clr, const char *filename);
    static void convertToGrayscale(const char *inputFile, const char *outputFile);


};
#endif //ADVANCEDSCRIPTING2_IMAGEOUTPUT_H
