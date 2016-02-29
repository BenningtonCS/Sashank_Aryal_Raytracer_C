#include <iostream>
#include "Image.h"


using namespace std;

int main() {
    uint8_t colors[]={200,100,25,1};
    Image::drawColoredBMP(300,300,colors,"myColor2.bmp");
    Image::convertToGrayscale("smile.bmp","smile2.bmp");
    return 0;
}