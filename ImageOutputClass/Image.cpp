//
// Created by Sashank on 2/28/2016.
//

#include "Image.h"
#include "EasyBMP/EasyBMP.h"
void Image::drawColoredBMP(int width, int height,uint8_t colors[4], const char* filename) {
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
void Image::convertToGrayscale(const char *inputFile, const char *outputFile) {
        BMP myImage;
        myImage.ReadFromFile(inputFile);
        for (int i = 0; i < myImage.TellWidth(); i++) {
            for (int j = 0; j < myImage.TellHeight(); j++) {
                uint8_t grayScaleValue = uint8_t(
                        floor((myImage(i, j)->Red * 0.299 +
                                myImage(i, j)->Blue * 0.587 +
                                myImage(i, j)->Green * 0.114)));
                ebmpBYTE castedGSValue = (ebmpBYTE) grayScaleValue;
                myImage(i, j)->Red = castedGSValue;
                myImage(i, j)->Green = castedGSValue;
                myImage(i, j)->Blue = castedGSValue;
            }
        }
myImage.WriteToFile(outputFile);
}