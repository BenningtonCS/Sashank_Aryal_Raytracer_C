//
// Created by Sashank on 3/9/2016.
//

#ifndef RAYTRACERC_SHAPE_H
#define RAYTRACERC_SHAPE_H
#include "../Color/Color.h"
#include "../Vector3D/Vector3D.h"
#include "../Ray/Ray.h"
#include "../Algebra/Matrix.h"

// Base class
class Shape{
private:
    void setInverseOfTransformationMatrix(){
        //Separate ro
    }
protected:
    float ambience;
    Matrix4x4 transformationMatrix;
    Matrix4x4 inverseOfTransformationMatix;
public:
    Shape(float amb){
        ambience = amb;
        setInverseOfTransformationMatrix();
    }
    virtual const ColorRGB getColor() = 0;
    virtual const double rayIntersectionDistance(Ray r) = 0;      //Distance from the origin of ray(camera) to the point of intersection
    virtual const Vector3D getNormalAt(Vector3D point) = 0;

    const float getAmbience(){
        return this->ambience;
    }

    const void scaleMatrixXYZBy(const Vector3D & vec){
        transformationMatrix = transformationMatrix.scaleMatrixXYZBy(vec);
        inverseOfTransformationMatix = inverseOfTransformationMatix.scaleMatrixXYZBy(1 / vec);

    }

    const void scaleUniformBy(double factor){
        //transformationMatrix
    }

    const void rotateBy(Vector3D){

    }

    const void translateBy(Vector3D coordinate) {
        // Write the transformation matrix
        Matrix4x4 translationMatrix;
        translationMatrix.mat[0][3] = coordinate.getX();
        translationMatrix.mat[1][3] = coordinate.getY();
        translationMatrix.mat[2][3] = coordinate.getZ();
        Matrix4x4 inverseOfTranslationMatrix = getInverseOfTranslationMatrix(translationMatrix);
    }

    const Matrix4x4 getInverseTransformationMatrix(){
            return inverseOfTransformationMatix;
    };

    const Matrix4x4 getTransformationMatrix(){
            return transformationMatrix;
    };
};

#endif //RAYTRACERC_SHAPE_H