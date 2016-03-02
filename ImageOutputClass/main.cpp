#include <iostream>
#include "Vector3D/Vector3D.h"

using namespace std;
using namespace Vector;
int main() {
    Vector3D test1(2.33,23.4,-2);
    Vector3D test2(3.2,4.5,9);
    cout << "Before overloading, it is.."<<endl;
    cout << "For test1, it is " << test1.getX()<<" "<<test1.getY()<<" "<<test1.getZ()<<endl;
    cout << "For test1, it is " << test2.getX()<<" "<<test2.getY()<<" "<<test2.getZ()<<endl;
    Vector3D addTests = test1 + test2;
    cout << "For test1, it is " << addTests.getX()<<" "<<addTests.getY()<<" "<<addTests.getZ()<<endl;

    cout << "Still working on it..." << endl;
    return 0;
}