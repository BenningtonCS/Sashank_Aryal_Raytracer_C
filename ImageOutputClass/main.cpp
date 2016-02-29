#include <iostream>
#include "ImageOutput.h"


using namespace std;

int main() {
    uint8_t colors[]={25,250,25,2};
    ImageOutput::draw(300,300,colors,"myColor.bmp");
    return 0;
}