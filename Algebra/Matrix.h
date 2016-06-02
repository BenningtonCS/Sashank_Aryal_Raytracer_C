//
// Created by Sashank on 4/20/2016.
//

#ifndef RAYTRACERC_MATRIX_H
#define RAYTRACERC_MATRIX_H

#include <iostream>
#include <ctime>
#include "../Vector4D/Vector4D.h"
#include "../Vector3D/Vector3D.h"

using namespace Vector;

class Matrix4x4{
public:
    double mat[4][4] = {{1, 0, 0, 0},
                        {0, 1, 0, 0},
                        {0, 0, 1, 0},
                        {0, 0, 0, 1}};


    const Matrix4x4 transposeMatrix() const{
        Matrix4x4 returnMatrix;
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                returnMatrix.mat[i][j] = this->mat[j][i];
            }
        }
        return returnMatrix;
    }

};
static inline const Matrix4x4 getScalingMatrixXYZ(const Vector3D &);
static inline const Matrix4x4 getUniformScalingMatrix(const double);
static inline const Vector4D operator*(const Matrix4x4 &, const Vector4D &);
static inline const Matrix4x4 operator*(const Matrix4x4 &, const Matrix4x4 &);
static inline const Matrix4x4 getTranslatingMatrix(const Vector3D &);
static inline const Matrix4x4 getRotatingMatrixAbout_X_Axis(const double);
static inline const Matrix4x4 getRotatingMatrixAbout_Y_Axis(const double);
static inline const Matrix4x4 getRotatingMatrixAbout_Z_Axis(const double);

static inline const Matrix4x4 operator*(const Matrix4x4 & A, const Matrix4x4 & B){
    Matrix4x4 returnMatrix;
    returnMatrix.mat[0][0] = A.mat[0][0] * B.mat[0][0] + A.mat[0][1] * B.mat[1][0] + A.mat[0][2] * B.mat[2][0] + A.mat[0][3] * B.mat[3][0];
    returnMatrix.mat[0][1] = A.mat[0][0] * B.mat[0][1] + A.mat[0][1] * B.mat[1][1] + A.mat[0][2] * B.mat[2][1] + A.mat[0][3] * B.mat[3][1];
    returnMatrix.mat[0][2] = A.mat[0][0] * B.mat[0][2] + A.mat[0][1] * B.mat[1][2] + A.mat[0][2] * B.mat[2][2] + A.mat[0][3] * B.mat[3][2];
    returnMatrix.mat[0][3] = A.mat[0][0] * B.mat[0][3] + A.mat[0][1] * B.mat[1][3] + A.mat[0][2] * B.mat[2][3] + A.mat[0][3] * B.mat[3][3];
    returnMatrix.mat[1][0] = A.mat[1][0] * B.mat[0][0] + A.mat[1][1] * B.mat[1][0] + A.mat[1][2] * B.mat[2][0] + A.mat[1][3] * B.mat[3][0];
    returnMatrix.mat[1][1] = A.mat[1][0] * B.mat[0][1] + A.mat[1][1] * B.mat[1][1] + A.mat[1][2] * B.mat[2][1] + A.mat[1][3] * B.mat[3][1];
    returnMatrix.mat[1][2] = A.mat[1][0] * B.mat[0][2] + A.mat[1][1] * B.mat[1][2] + A.mat[1][2] * B.mat[2][2] + A.mat[1][3] * B.mat[3][2];
    returnMatrix.mat[1][3] = A.mat[1][0] * B.mat[0][3] + A.mat[1][1] * B.mat[1][3] + A.mat[1][2] * B.mat[2][3] + A.mat[1][3] * B.mat[3][3];
    returnMatrix.mat[2][0] = A.mat[2][0] * B.mat[0][0] + A.mat[2][1] * B.mat[1][0] + A.mat[2][2] * B.mat[2][0] + A.mat[2][3] * B.mat[3][0];
    returnMatrix.mat[2][1] = A.mat[2][0] * B.mat[0][1] + A.mat[2][1] * B.mat[1][1] + A.mat[2][2] * B.mat[2][1] + A.mat[2][3] * B.mat[3][1];
    returnMatrix.mat[2][2] = A.mat[2][0] * B.mat[0][2] + A.mat[2][1] * B.mat[1][2] + A.mat[2][2] * B.mat[2][2] + A.mat[2][3] * B.mat[3][2];
    returnMatrix.mat[2][3] = A.mat[2][0] * B.mat[0][3] + A.mat[2][1] * B.mat[1][3] + A.mat[2][2] * B.mat[2][3] + A.mat[2][3] * B.mat[3][3];
    return returnMatrix;
}

static inline const Vector4D operator*(const Matrix4x4& m, const Vector4D& vec){
    double x = m.mat[0][0] * vec.getX() + m.mat[0][1] * vec.getY() + m.mat[0][2] * vec.getZ() + m.mat[0][3] * vec.getW();
    double y = m.mat[1][0] * vec.getX() + m.mat[1][1] * vec.getY() + m.mat[1][2] * vec.getZ() + m.mat[1][3] * vec.getW();
    double z = m.mat[2][0] * vec.getX() + m.mat[2][1] * vec.getY() + m.mat[2][2] * vec.getZ() + m.mat[2][3] * vec.getW();
    double w = m.mat[3][0] * vec.getX() + m.mat[3][1] * vec.getY() + m.mat[3][2] * vec.getZ() + m.mat[3][3] * vec.getW();
    return Vector4D(x, y, z, w);
}
static inline const Matrix4x4 getInverseOfTranslationMatrix(const Matrix4x4 & translationMatrix){
    // Remember that the inverse of a translation matrix is the translation matrix with the opposite signs of each of the translation components
    Matrix4x4 returnMatrix;
    returnMatrix = translationMatrix;
    returnMatrix.mat[0][3] *= -1;
    returnMatrix.mat[1][3] *= -1;
    returnMatrix.mat[2][3] *= -1;
    returnMatrix.mat[3][3] *= 1;
    return returnMatrix;
}

static inline const Matrix4x4 getInverseOfRotationMatrix(const Matrix4x4 & rotationMatrix){
    //Remember that the inverse of a rotation matrix is the transpose of the rotation matrix
    Matrix4x4 returnMatrix;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            returnMatrix.mat[i][j] = rotationMatrix.mat[j][i];
        }
    }
}

static inline const Matrix4x4 getUniformScalingMatrix(const double s){
    return getScalingMatrixXYZ(Vector3D(s, s, s));
}

static inline const Matrix4x4 getScalingMatrixXYZ(const Vector3D & vec){
        Matrix4x4 scalingMatrix;
        scalingMatrix.mat[0][0] = vec.getX();
        scalingMatrix.mat[1][1] = vec.getY();
        scalingMatrix.mat[2][2] = vec.getZ();
        return scalingMatrix;
}

static inline const Matrix4x4 getTranslatingMatrix(const Vector3D & vec){
    Matrix4x4 translationMatrix;
    translationMatrix.mat[0][3] = vec.getX();
    translationMatrix.mat[1][3] = vec.getY();
    translationMatrix.mat[2][3] = vec.getZ();
    return translationMatrix;
}

static inline const Matrix4x4 getRotatingMatrixAbout_X_Axis(const double angleInRads){
    Matrix4x4 rotationMatrix;
    rotationMatrix.mat[1][1] = cos(angleInRads);
    rotationMatrix.mat[1][2] = -sin(angleInRads);
    rotationMatrix.mat[2][1] = sin(angleInRads);
    rotationMatrix.mat[2][2] = cos(angleInRads);
    return rotationMatrix;
}

static inline const Matrix4x4 getRotatingMatrixAbout_Y_Axis(const double angleInRads){
    Matrix4x4 rotationMatrix;
    rotationMatrix.mat[0][0] = cos(angleInRads);
    rotationMatrix.mat[0][2] = sin(angleInRads);
    rotationMatrix.mat[2][0] = -sin(angleInRads);
    rotationMatrix.mat[2][2] = cos(angleInRads);
    return rotationMatrix;
}

static inline const Matrix4x4 getRotatingMatrixAbout_Z_Axis(const double angleInRads){
    Matrix4x4 rotationMatrix;
    rotationMatrix.mat[0][0] = cos(angleInRads);
    rotationMatrix.mat[0][1] = -sin(angleInRads);
    rotationMatrix.mat[1][0] = sin(angleInRads);
    rotationMatrix.mat[1][1] = cos(angleInRads);
    return rotationMatrix;
}
#endif //RAYTRACERC_MATRIX_H