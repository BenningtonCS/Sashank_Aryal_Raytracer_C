//
// Created by Sashank on 5/3/2016.
//

#ifndef RAYTRACERC_VECTOR4D_H
#define RAYTRACERC_VECTOR4D_H

#include <cmath>

namespace Vector {
    class Vector4D {
    private:
        //Set x, y, z private. Encapsulate
        double x;
        double y;
        double z;
        double w;
    public:
        // Default constructor: create a vector whose x, y, z components are all zero.
        Vector4D();
        Vector4D(const double _x, const double _y, const double _z, const double _w);

        ////////////////////////////////////////////////////////////////////////
        // GETTERS AND SETTERS //
        const double getX() const;
        const double getY() const;
        const double getZ() const;
        const double getW() const;

    };


/* ========================================================================
 * =====================OPERATOR OVERLOADING===============================
*/

// This + operator now can be used to add two Vector objects.
    inline Vector4D operator+(const Vector4D &a, const Vector4D &b){
        return Vector4D(a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ(), a.getW() + b.getW());
    };

    inline Vector4D operator+(const double a, const Vector4D &b){
        return Vector4D(b.getX() + a, b.getY() + a, b.getZ() + a, b.getW() + a);
    }

// This - operator now can be used to subtract two Vector objects.
    inline Vector4D operator-(const Vector4D &a, const Vector4D &b) {
        return Vector4D(a.getX() - b.getX(), a.getY() - b.getY(), a.getZ() - b.getZ(), a.getW() - b.getW());
    }


// Allows me to negate the vector, reflecting it across the origin into the opposite octant.
    inline Vector4D operator-(const Vector4D &a) {
        double firstComponent = a.getX() == 0 ? 0 : -a.getX();
        double secondComponent = a.getY() == 0 ? 0 : -a.getY();
        double thirdComponent = a.getZ() == 0 ? 0 : -a.getZ();
        double fourthComponent = a.getW() == 0? 0 : -a.getW();
        return Vector4D(firstComponent, secondComponent, thirdComponent, fourthComponent);
    }

// Returns dot Product
    inline double DotProduct(const Vector4D &a, const Vector4D &b) {
        return (a.getX() * b.getX()) + (a.getY() * b.getY()) + (a.getZ() * b.getZ()) + (a.getW() * b.getW());
    }


// Scales a factor by a real number
    inline Vector4D operator*(double s, const Vector4D &v) {
        return Vector4D(s * v.getX(), s * v.getY(), s * v.getZ(), s* v.getW());
    }

// Same as above
    inline Vector4D operator/(const Vector4D &v, double s) {
        return Vector4D(v.getX() / s, v.getY() / s, v.getZ() / s, v.getW() / s);
    }

    inline Vector4D operator/(double s, const Vector4D &v) {
        return Vector4D(s / v.getX(), s / v.getY(), s / v.getZ(), s / v.getW());
    }
}



#endif //RAYTRACERC_VECTOR4D_H
