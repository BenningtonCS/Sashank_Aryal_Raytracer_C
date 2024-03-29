//
// Created by Sashank on 3/22/2016.
//

#ifndef RAYTRACERC_ALGEBRA_H
#define RAYTRACERC_ALGEBRA_H

#include <map>
#include <cmath>

class Algebra {
public:
    static const double floatDivision(const double a, const double b);
    static double deg2rad (double degrees);
    static double getRandomBetween(double min, double max);
private:
    static int sign(double x);
};


#endif //RAYTRACERC_ALGEBRA_H
