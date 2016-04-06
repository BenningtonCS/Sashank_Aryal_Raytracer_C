//
// Created by Sashank on 3/8/2016.
//

#ifndef RAYTRACERC_VECTOR3D_H
#define RAYTRACERC_VECTOR3D_H

#include <cmath>

namespace Vector {
    class Vector3D {
    private:
        //Set x, y, z private. Encapsulate
        double x;
        double y;
        double z;
    public:
        // Default constructor: create a vector whose x, y, z components are all zero.
        Vector3D();
        Vector3D(const double _x, const double _y, const double _z);

        ////////////////////////////////////////////////////////////////////////
        // GETTERS AND SETTERS //
        const double getX() const;
        const double getY() const;
        const double getZ() const;
        void setX(const double x);
        void setY(const double y);
        void setZ(const double z);



        ///////////////////////////////////////////////////////////////////////////
        /* Returns the square of the magnitude of this vector.
         more efficient than computing the magnitude itself,and is enough for comparing two vectors to see which
         is longer or shorter.
         */
        const double magnitudeSquared() const;
        const double magnitude() const;
        const Vector3D unitVector() const;
    };


/* ========================================================================
 * ========================================================================
 * ========================================================================
 * ========================================================================
 * =====================OPERATOR OVERLOADING===============================
 * ========================================================================
 * ========================================================================
 * ========================================================================
 * ========================================================================
 */

// This + operator now can be used to add two Vector objects.
    inline Vector3D operator+(const Vector3D &a, const Vector3D &b){
        return Vector3D(a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
    };

    inline Vector3D operator+(const double a, const Vector3D &b){
        return Vector3D(b.getX() + a, b.getY() + a, b.getZ() + a);
    }

// This - operator now can be used to subtract two Vector objects.
    inline Vector3D operator-(const Vector3D &a, const Vector3D &b) {
        return Vector3D(a.getX() - b.getX(), a.getY() - b.getY(), a.getZ() - b.getZ());
    }


// Allows me to negate the vector, reflecting it across the origin into the opposite octant.
    inline Vector3D operator-(const Vector3D &a) {
        double firstComponent = a.getX() == 0 ? 0 : -a.getX();
        double secondComponent = a.getY() == 0 ? 0 : -a.getY();
        double thirdComponent = a.getZ() == 0 ? 0 : -a.getZ();
        return Vector3D(firstComponent, secondComponent, thirdComponent);
    }

// Returns dot Product
    inline double DotProduct(const Vector3D &a, const Vector3D &b) {
        return (a.getX() * b.getX()) + (a.getY() * b.getY()) + (a.getZ() * b.getZ());
    }

// Returns cross product of two vectors
    inline Vector3D CrossProduct(const Vector3D &a, const Vector3D &b) {
        double firstComponent = (a.getY() * b.getZ())- (a.getZ() * b.getY());

        double secondComponent = (a.getZ() * b.getX()) - (a.getX() * b.getZ());

        double thirdComponent = (a.getX() * b.getY()) - (a.getY() * b.getX());

        return Vector3D(firstComponent, secondComponent, thirdComponent);
    }

// Scales a factor by a real number
    inline Vector3D operator*(double s, const Vector3D &v) {
        return Vector3D(s * v.getX(), s * v.getY(), s * v.getZ());
    }

// Same as above
    inline Vector3D operator/(const Vector3D &v, double s) {
        return Vector3D(v.getX() / s, v.getY() / s, v.getZ() / s);
    }

    inline Vector3D operator/(double s, const Vector3D &v) {
        return Vector3D(s / v.getX(), s / v.getY(), s / v.getZ());
    }
}


#endif //RAYTRACERC_VECTOR3D_H
