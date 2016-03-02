#include <iostream>
#include "Image.h"
#include "Color.h"


using namespace std;

int main() {
    int width = 600;
    int height = 800;
    Color test[width*height];
    Image::drawColoredBMP(300,300,colors,"testColor.bmp");
    Image::convertToGrayscale("smile.bmp","smile2.bmp");
     */
    return 0;
}