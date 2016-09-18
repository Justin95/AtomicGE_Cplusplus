#include "MathUtil.h"

#include <math.h>
#include <iostream>
//Matrix functions

Matrix4x4F swapRowsCols(Matrix4x4F m){
    Matrix4x4F swapped = {
        m.m00, m.m10, m.m20, m.m30,
        m.m01, m.m11, m.m21, m.m31,
        m.m02, m.m12, m.m22, m.m32,
        m.m03, m.m13, m.m23, m.m33
    };
    return swapped;
}

Matrix4x4F getIdentity(){
    Matrix4x4F identity = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1
    };
    return identity;
}

Matrix4x4F getZeroMatrix(){
    Matrix4x4F zero = {
        0,0,0,0,
        0,0,0,0,
        0,0,0,0,
        0,0,0,0
    };
    return zero;
}


Matrix4x4F getXRotMatrix(float xRot){
    Matrix4x4F xRotMatrix = {
        1,               0,                 0,0,
        0,(float)cos(xRot), (float)-sin(xRot),0,
        0,(float)sin(xRot), (float) cos(xRot),0,
        0,               0,                 0,1
    };
    return xRotMatrix;
}


Matrix4x4F getYRotMatrix(float yRot){
    Matrix4x4F yRotMatrix = {
        (float) cos(yRot),0, (float)sin(yRot),0,
                        0,1,                0,0,
        (float)-sin(yRot),0, (float)cos(yRot),0,
                        0,0,                0,1
    };
    return yRotMatrix;
}


Matrix4x4F getZRotMatrix(float zRot){
    Matrix4x4F zRotMatrix = {
        (float)cos(zRot), (float)-sin(zRot),0,0,
        (float)sin(zRot), (float) cos(zRot),0,0,
                       0,                 0,1,0,
                       0,                 0,0,1 
    };
    return zRotMatrix;
}


Matrix4x4F operator* (Matrix4x4F a, float b){
    Matrix4x4F result = {
        a.m00 * b, a.m01 * b, a.m02 * b, a.m03 * b,
        a.m10 * b, a.m11 * b, a.m12 * b, a.m13 * b,
        a.m20 * b, a.m21 * b, a.m22 * b, a.m23 * b,
        a.m30 * b, a.m31 * b, a.m32 * b, a.m33 * b
    };
    return result;
}

Matrix4x4F operator* (Matrix4x4F a, Matrix4x4F b){ //http://i.stack.imgur.com/iRxxe.png
    Matrix4x4F result = {
        a.m00 * b.m00 + a.m01 * b.m10 + a.m02 * b.m20 + a.m03 * b.m30, //m00
        a.m00 * b.m01 + a.m01 * b.m11 + a.m02 * b.m21 + a.m03 * b.m31, //m01
        a.m00 * b.m02 + a.m01 * b.m12 + a.m02 * b.m22 + a.m03 * b.m32, //m02
        a.m00 * b.m03 + a.m01 * b.m13 + a.m02 * b.m23 + a.m03 * b.m33, //m03
        
        a.m10 * b.m00 + a.m11 * b.m10 + a.m12 * b.m20 + a.m13 * b.m30, //m10
        a.m10 * b.m01 + a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31, //m11
        a.m10 * b.m02 + a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32, //m12
        a.m10 * b.m03 + a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33, //m13
        
        a.m20 * b.m00 + a.m21 * b.m10 + a.m22 * b.m20 + a.m23 * b.m30, //m20
        a.m20 * b.m01 + a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31, //m21
        a.m20 * b.m02 + a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32, //m22
        a.m20 * b.m03 + a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33, //m23
        
        a.m30 * b.m00 + a.m31 * b.m10 + a.m32 * b.m20 + a.m33 * b.m30, //m30
        a.m30 * b.m01 + a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31, //m31
        a.m30 * b.m02 + a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32, //m32
        a.m30 * b.m03 + a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33  //m33
    };
    return result; //the best I've ever felt writing a return statement
}

Matrix4x4F calculateModelMatrix(Vector3F position, Vector3F rotation, float scale){
    Vector3F radianRotation;
    radianRotation.x = -toRadians(rotation.x);
    radianRotation.y = -toRadians(rotation.y);
    radianRotation.z = -toRadians(rotation.z);
    // scale, rotate, translate, always in that order.
    //scale
    Matrix4x4F modelMatrix = getIdentity();
    modelMatrix.m00 *= scale;
    modelMatrix.m11 *= scale;
    modelMatrix.m22 *= scale;
    
    //rotate, double check this if weird stuff happens
    modelMatrix = modelMatrix * getYRotMatrix(radianRotation.y); //usually do y, z, x
    modelMatrix = modelMatrix * getZRotMatrix(radianRotation.z);
    modelMatrix = modelMatrix * getXRotMatrix(radianRotation.x);
    
    //translate, double check this if weird stuff happens
    modelMatrix.m03 += position.x;
    modelMatrix.m13 += position.y;
    modelMatrix.m23 += position.z;
    
    return modelMatrix;
}


Matrix4x4F calculateModelMatrix(Vector3D position, Vector3D rotation, float scale){
    Vector3F pos = {
        (float)position.x,
        (float)position.y,
        (float)position.z
    };
    
    Vector3F rot = {
        (float)rotation.x,
        (float)rotation.y,
        (float)rotation.z
    };
    return calculateModelMatrix(pos, rot, scale);
}


Matrix4x4F calculateViewMatrix(Vector3F position, Vector3F rotation){
    Vector3F pos = position * -1;
    Vector3F rot = rotation * -1;
    return calculateModelMatrix(pos, rot, 1);
}


Matrix4x4F calculateViewMatrix(Vector3D position, Vector3D rotation){
    Vector3D pos = position * -1;
    Vector3D rot = rotation * -1;
    return calculateModelMatrix(pos, rot, 1);
}


Matrix4x4F calculateProjectionMatrix(float fov, float aspectRatio, float nearClip, float farClip){
    float yScale = (float) (1.0/tan(toRadians(fov / 2)));
    float xScale = yScale / aspectRatio;
    Matrix4x4F proj = getZeroMatrix();
    
    proj.m00 = xScale;
    proj.m11 = yScale;
    proj.m22 = -((farClip + nearClip) / (farClip - nearClip));
    proj.m32 = -1;
    proj.m23 = -((2 * nearClip * farClip) / (farClip - nearClip));
    
    return proj;
}

//Vector functions

Vector3D getInverse(Vector3D v){
    return v * -1;
}

Vector3F getInverse(Vector3F v){
    return v * -1;
}


double getMagnitude(Vector3D v){
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float getMagnitude(Vector3F v){
    return (float)sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

double getDotProduct(Vector3D a, Vector3D b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float getDotProduct(Vector3F a, Vector3F b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}


Vector3D getCrossProduct(Vector3D a, Vector3D b){
    Vector3D result = {
        a.y * b.z - a.z * b.y, //x
        a.x * b.z - a.z * b.x, //y
        a.x * b.y - a.y * b.x  //z
    };
    return result;
}

Vector3F getCrossProduct(Vector3F a, Vector3F b){
    Vector3F result = {
        a.y * b.z - a.z * b.y, //x
        a.x * b.z - a.z * b.x, //y
        a.x * b.y - a.y * b.x  //z
    };
    return result;
}

Vector3D operator*(Vector3D v, double a){
    Vector3D result = {
        v.x * a,
        v.y * a,
        v.z * a
    };
    return result;
}

Vector3F operator*(Vector3F v, float a){
    Vector3F result = {
        v.x * a,
        v.y * a,
        v.z * a
    };
    return result;
}

Vector3D getUnitVector(Vector3D v){
    double magnitude = getMagnitude(v);
    Vector3D result = {
        v.x / magnitude,
        v.y / magnitude,
        v.z / magnitude
    };
    return result;
}

Vector3F getUnitVector(Vector3F v){
    float magnitude = (float)getMagnitude(v);
    Vector3F result = {
        v.x / magnitude,
        v.y / magnitude,
        v.z / magnitude
    };
    return result;
}

//Math functions


double toRadians(double angle){
    return angle * PI / 180;
}


double toDegrees(double angle){
    return angle * 180 / PI;
}
