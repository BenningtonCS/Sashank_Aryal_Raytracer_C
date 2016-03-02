//
// Created by Sashank on 3/2/2016.
//
#include <math.h>
#ifndef IMAGEOUTPUTCLASS_VECTOR_H
#define IMAGEOUTPUTCLASS_VECTOR_H
#endif //IMAGEOUTPUTCLASS_VECTOR_H

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
        const double MagnitudeSquared() const;
        const double Magnitude() const;
        const Vector3D UnitVector() const;

        // Operator overloading
        Vector3D &operator*=(const double factor);

        //Vector3D &operator+=(const Vector3D &other);
    };

    inline Vector3D operator+(const Vector3D &a, const Vector3D &b){
        return Vector3D(a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
    };

}
/*














//------------------------------------------------------------------------

    inline Vector3D operator+(const Vector3D &a, const Vector3D &b) {
        return Vector3D(a.x + b.x, a.y + b.y, a.z + b.z);
    }

    inline Vector3D operator-(const Vector3D &a, const Vector3D &b) {
        return Vector3D(a.x - b.x, a.y - b.y, a.z - b.z);
    }

    inline Vector3D operator-(const Vector3D &a) {
        return Vector3D(-a.x, -a.y, -a.z);
    }

    inline double DotProduct(const Vector3D &a, const Vector3D &b) {
        return (a.getX() * b.getX()) + (a.getY() * b.getY()) + (a.getZ() * b.getZ());
    }

    inline Vector3D CrossProduct(const Vector3D &a, const Vector3D &b) {
        return Vector3D(
                (a.y * b.z) - (a.z * b.y),
                (a.z * b.x) - (a.x * b.z),
                (a.x * b.y) - (a.y * b.x));
    }

    inline Vector3D operator*(double s, const Vector3D &v) {
        return Vector3D(s * v.x, s * v.y, s * v.z);
    }

    inline Vector3D operator/(const Vector3D &v, double s) {
        return Vector3D(v.x / s, v.y / s, v.z / s);
    }

}
*/
