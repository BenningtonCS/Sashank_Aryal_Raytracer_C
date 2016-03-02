#include <iostream>
#include "Image.h"
#include "Color.h"
#include "Vector.h"

using namespace std;
using namespace Vector;
int main() {
    int width = 600;
    int height = 800;
    int resolution = width * height;
    Color test[resolution];
    Image::drawColoredBMP(width,height,test,"testColor.bmp");
    Image::convertToGrayscale("smile.bmp","smile2.bmp");
    return 0;
}