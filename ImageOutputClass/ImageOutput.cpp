//
// Created by Sashank on 2/28/2016.
//

#include "ImageOutput.h"
#include "EasyBMP/EasyBMP.h"
void ImageOutput::draw(int width, int height,uint8_t colors[4], const char* filename) {
    BMP myImage;
    myImage.SetSize(width,height);
    myImage.SetBitDepth(32);
    for (int i=0;i<width;i++){
        for (int j=0;j<height;j++){
            myImage(i,j)->Red=colors[0];
            myImage(i,j)->Green=colors[1];
            myImage(i,j)->Blue=colors[2];
            myImage(i,j)->Alpha=colors[3];
        }
    }
    std::cout <<"Printing to file..."<<filename<<std::endl;
    myImage.WriteToFile(filename);
    std::cout <<"Done printing to file..."<<filename<<std::endl;
}