//
// Created by Sashank on 3/9/2016.
//

#ifndef RAYTRACERC_POINT3D_H
#define RAYTRACERC_POINT3D_H
class Point3D{
private:
    double x;
    double y;
    double z;
public:

    Point3D(double x, double y, double z) : x(x), y(y), z(z) { }
    Point3D(){
        x = 0;
        y = 0;
        z = 0;
    };


    double getX() const {
        return x;
    }

    void setX(double x) {
        Point3D::x = x;
    }

    double getY() const {
        return y;
    }

    void setY(double y) {
        Point3D::y = y;
    }

    double getZ() const {
        return z;
    }

    void setZ(double z) {
        Point3D::z = z;
    }
};
#endif //RAYTRACERC_POINT3D_H
