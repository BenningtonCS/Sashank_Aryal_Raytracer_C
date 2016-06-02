//
// Created by Sashank on 3/9/2016.
//

#ifndef RAYTRACERC_SHAPE_H
#define RAYTRACERC_SHAPE_H
#include "../Color/Color.h"
#include "../Vector3D/Vector3D.h"
#include "../Ray/Ray.h"
#include "../Algebra/Matrix.h"
#include "../Algebra/Algebra.h"
#include "../Material/Material.h"

// Abstract Base class
class Shape{

protected:
    Material material;
    Matrix4x4 transformationMatrix;
    Matrix4x4 inverseOfTransformationMatrix;
public:
    Shape(const Material & material){
        this->material = material;
    }

    Shape(){
        this->material = Material();
    }

    virtual const double rayIntersectionDistance(Ray r) = 0;      //Distance from the origin of ray(camera) to the point of intersection
    virtual const Vector3D getNormalAt(Vector3D point) = 0;

    Material getMaterial(){
        return material;
    }

    const void setMaterial(const Material & material){
        this->material = material;
    }
    const void scaleMatrixXYZBy(const Vector3D & vec){
        transformationMatrix = getScalingMatrixXYZ(vec) * transformationMatrix;
        inverseOfTransformationMatrix = inverseOfTransformationMatrix * getScalingMatrixXYZ(1/vec);
    }

    const void scaleUniformBy(double factor){
        transformationMatrix = getUniformScalingMatrix(factor) * transformationMatrix;
        inverseOfTransformationMatrix = inverseOfTransformationMatrix * getUniformScalingMatrix(1/factor);
    }

    const void rotateAround_X_By(double angleInDegrees){
        double angleInRads = Algebra::deg2rad(angleInDegrees);
        transformationMatrix = getRotatingMatrixAbout_X_Axis(angleInRads) * transformationMatrix;
        inverseOfTransformationMatrix = inverseOfTransformationMatrix * getRotatingMatrixAbout_X_Axis(-angleInRads);
    }

    const void rotateAround_Y_By(double angleInDegrees){
        double angleInRads = Algebra::deg2rad(angleInDegrees);
        transformationMatrix = getRotatingMatrixAbout_Y_Axis(angleInRads) * transformationMatrix;
        inverseOfTransformationMatrix = inverseOfTransformationMatrix * getRotatingMatrixAbout_Y_Axis(-angleInRads);
    }


    const void rotateAround_Z_By(double angleInDegrees){
        double angleInRads = Algebra::deg2rad(angleInDegrees);
        transformationMatrix = getRotatingMatrixAbout_Z_Axis(angleInRads) * transformationMatrix;
        inverseOfTransformationMatrix = inverseOfTransformationMatrix * getRotatingMatrixAbout_Z_Axis(-angleInRads);
    }

    const void translateBy(Vector3D coordinate) {
        transformationMatrix = getTranslatingMatrix(coordinate) * transformationMatrix;
        inverseOfTransformationMatrix = inverseOfTransformationMatrix * getTranslatingMatrix(-coordinate);
    }

    const Matrix4x4 getInverseTransformationMatrix(){
            return inverseOfTransformationMatrix;
    };

    const Matrix4x4 getTransformationMatrix(){
            return transformationMatrix;
    };
};

#endif //RAYTRACERC_SHAPE_H