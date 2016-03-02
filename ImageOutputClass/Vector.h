//
// Created by Sashank on 3/2/2016.
//

#include <math.h>
#ifndef IMAGEOUTPUTCLASS_VECTOR_H
#define IMAGEOUTPUTCLASS_VECTOR_H
#endif //IMAGEOUTPUTCLASS_VECTOR_H

namespace Vector {
    class Vector {

    private:
        //Set x, y, z private. Encapsulate
        double x;
        double y;
        double z;

    public:

        // Default constructor: create a vector whose x, y, z components are all zero.



        Vector():
                x(0.0), y(0.0), z(0.0) {}

        // This constructor initializes a vector to any desired component values.
        Vector(double _x, double _y, double _z):
                x(_x), y(_y), z(_z) {}

        ////////////////////////////////////////////////////////////////////////
        // GETTERS AND SETTERS //
        const double getX(){
            return x;
        }
        const double getY(){
            return y;
        }
        const double getZ() {
            return z;
        }


        void setX(const double x) {
            Vector::x = x;
        }

        void setY(const double y) {
            Vector::y = y;
        }

        void setZ(const double z) {
            Vector::z = z;
        }

        ///////////////////////////////////////////////////////////////////////////

        /* Returns the square of the magnitude of this vector.
         more efficient than computing the magnitude itself,and is enough for comparing two vectors to see which
         is longer or shorter.
         */
        const double MagnitudeSquared() const {
            return (x * x) + (y * y) + (z * z);
        }

        const double Magnitude() const {
            return sqrt(MagnitudeSquared());
        }

        const Vector UnitVector() const {
            const double mag = Magnitude();
            return Vector(x / mag, y / mag, z / mag);
        }



























    /*
        Vector &operator*=(const double factor) {
            x *= factor;
            y *= factor;
            z *= factor;
            return *this;
        }

        Vector &operator+=(const Vector &other) {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }
      */
    };


//------------------------------------------------------------------------
/*
    inline Vector operator+(const Vector &a, const Vector &b) {
        return Vector(a.x + b.x, a.y + b.y, a.z + b.z);
    }

    inline Vector operator-(const Vector &a, const Vector &b) {
        return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
    }

    inline Vector operator-(const Vector &a) {
        return Vector(-a.x, -a.y, -a.z);
    }

    inline double DotProduct(const Vector &a, const Vector &b) {
        return (a.getX() * b.getX()) + (a.getY() * b.getY()) + (a.getZ() * b.getZ());
    }

    inline Vector CrossProduct(const Vector &a, const Vector &b) {
        return Vector(
                (a.y * b.z) - (a.z * b.y),
                (a.z * b.x) - (a.x * b.z),
                (a.x * b.y) - (a.y * b.x));
    }

    inline Vector operator*(double s, const Vector &v) {
        return Vector(s * v.x, s * v.y, s * v.z);
    }

    inline Vector operator/(const Vector &v, double s) {
        return Vector(v.x / s, v.y / s, v.z / s);
    }

}