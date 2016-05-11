//
// Created by Sashank on 4/20/2016.
//

#ifndef RAYTRACERC_MATRIX_H
#define RAYTRACERC_MATRIX_H

#include <iostream>
#include "../Vector4D/Vector4D.h"
#include "../Vector3D/Vector3D.h"

using namespace Vector;

class Matrix4x4{
public:
    double mat[4][4] = {{1, 0, 0, 0},
                        {0, 1, 0, 0},
                        {0, 0, 1, 0},
                        {0, 0, 0, 1}};

    Matrix4x4(){
    }

    
    const Matrix4x4 addMatrixTo(const Matrix4x4 & inputMatrix){
        Matrix4x4 returnMatrix;
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                returnMatrix.mat[i][j] = this->mat[i][j] + inputMatrix.mat[i][j];
            }
        }
        return returnMatrix;
    }

    const Matrix4x4 scaleMatrixUniformBy(double s){
        Matrix4x4 returnMatrix;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                returnMatrix.mat[i][j] = s * this->mat[i][j];
            }
        }
    }

    const Matrix4x4 scaleMatrixXYZBy(Vector3D vec){
        Matrix4x4 returnMatrix;
        returnMatrix = *this;
        returnMatrix.mat[0][0] *= vec.getX();
        returnMatrix.mat[1][1] *= vec.getY();
        returnMatrix.mat[2][2] *= vec.getZ();
        return returnMatrix;
    }

    const Matrix4x4 transposeMatrix(){
        Matrix4x4 returnMatrix;
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                returnMatrix.mat[i][j] = this->mat[j][i];
            }
        }
    }

};

static inline Matrix4x4 getInverseOfTranslationMatrix(const Matrix4x4 & translationMatrix){
    // Remember that the inverse of a translation matrix is the translation matrix with the opposite signs of each of the translation components
    Matrix4x4 returnMatrix;
    returnMatrix = translationMatrix;
    returnMatrix.mat[0][3] *= -1;
    returnMatrix.mat[1][3] *= -1;
    returnMatrix.mat[2][3] *= -1;
    returnMatrix.mat[3][3] *= 1;
    return returnMatrix;
}

static inline Matrix4x4 getInverseOfRotationMatrix(const Matrix4x4 & rotationMatrix){
    //Remember that the inverse of a rotation matrix is the transpose of the rotation matrix
    Matrix4x4 returnMatrix;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            returnMatrix.mat[i][j] = rotationMatrix.mat[j][i];
        }
    }
}

static inline Matrix4x4 multiply4x4Matrices(const Matrix4x4 & A, const Matrix4x4 & B){
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
    returnMatrix.mat[3][0] = A.mat[3][0] * B.mat[0][0] + A.mat[3][1] * B.mat[1][0] + A.mat[3][2] * B.mat[2][0] + A.mat[3][3] * B.mat[3][0];
    returnMatrix.mat[3][1] = A.mat[3][0] * B.mat[0][1] + A.mat[3][1] * B.mat[1][1] + A.mat[3][2] * B.mat[2][1] + A.mat[3][3] * B.mat[3][1];
    returnMatrix.mat[3][2] = A.mat[3][0] * B.mat[0][2] + A.mat[3][1] * B.mat[1][2] + A.mat[3][2] * B.mat[2][2] + A.mat[3][3] * B.mat[3][2];
    returnMatrix.mat[3][3] = A.mat[3][0] * B.mat[0][3] + A.mat[3][1] * B.mat[1][3] + A.mat[3][2] * B.mat[2][3] + A.mat[3][3] * B.mat[3][3];
}

static inline Vector3D operator*(const Matrix4x4& m, const Vector3D& vec){
    double x = m.mat[0][0] * vec.getX() + m.mat[0][1] * vec.getY() + m.mat[0][2] * vec.getZ();
    double y = m.mat[1][0] * vec.getX() + m.mat[1][1] * vec.getY() + m.mat[1][2] * vec.getZ();
    double z = m.mat[2][0] * vec.getX() + m.mat[2][1] * vec.getY() + m.mat[2][2] * vec.getZ();
    return Vector3D(x, y, z);
}
#endif //RAYTRACERC_MATRIX_H