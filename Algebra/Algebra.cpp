//
// Created by Sashank on 3/22/2016.
//

#include "Algebra.h"
#include <algorithm>
#include <ctime>

#define LARGEVALUE 1e10

const int Algebra::getKeyOfLeastValueFromMap(std::map<int, double> myMap) {
    double min = 10000;
    int minAt = 0;
    for (std::map<int, double>::iterator it = myMap.begin(); it!=myMap.end(); ++it){
        if (it->second < min){
            min = it->second;
            minAt = it->first;
        }
    }
    return minAt;
}


const double Algebra::floatDivision(const double a, const double b) {
    if (b == 0){
        if (a == 0) return 0;
    else return LARGEVALUE * sign(a);
}
    else {
        if (a == 0) return 0;
        else {
            if ((a + b) == a)                       //a is infinity
                return LARGEVALUE * sign(a) * sign(b);
        }
        return a / b;
    }
}


int Algebra::sign(double x)
{
    return (x == 0 ? 0 : (x < 0 ? -1 : 1));
}

double Algebra::deg2rad (double degrees) {
    return degrees * 4.0 * atan (1.0) / 180.0;
}


double Algebra::getRandomBetweenZeroAndOne() {
    return (double)rand()/RAND_MAX;
}