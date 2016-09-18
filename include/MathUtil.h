#ifndef MATHUTIL_H
#define MATHUTIL_H


#define PI 3.14159265358979323846

typedef struct Vector3D{
    double x;
    double y;
    double z;
}Vector3D;


typedef struct Vector3F{
    float x;
    float y;
    float z;
}Vector3F;


typedef struct Matrix4x4F {
    float m00, m01, m02, m03;
    float m10, m11, m12, m13;
    float m20, m21, m22, m23;
    float m30, m31, m32, m33;
}Matrix4x4F;

//Matrix functions

Matrix4x4F swapRowsCols(Matrix4x4F);

Matrix4x4F getIdentity();

Matrix4x4F getZeroMatrix();

Matrix4x4F getXRotMatrix(float xRot);

Matrix4x4F getYRotMatrix(float yRot);

Matrix4x4F getZRotMatrix(float zRot);

Matrix4x4F operator* (Matrix4x4F a, float b);

Matrix4x4F operator* (Matrix4x4F a, Matrix4x4F b);

/** \brief Creates a model matrix needed to translate and rotate a rendered object in space for drawing.
 *
 * \param position - The position vector of the object.
 * \param rotation - The rotation vector of the object.
 * \return A 4x4 model matrix
 *
 */     
Matrix4x4F calculateModelMatrix(Vector3F position, Vector3F rotation, float scale);

Matrix4x4F calculateModelMatrix(Vector3D position, Vector3D rotation, float scale);

/** \brief Creates a view matrix needed to translate and rotate the camera for drawing.
 *
 * \param position - The position vector of the camera.
 * \param rotation - The rotation vector of the camera.
 * \return A 4x4 view matrix
 *
 */     
Matrix4x4F calculateViewMatrix(Vector3F position, Vector3F rotation);

Matrix4x4F calculateViewMatrix(Vector3D position, Vector3D rotation);

/** \brief Creates a projection matrix needed to render a scene.
 *
 * \param fov - The field of vision
 * \param aspectRatio - The aspect ratio as a float. note: width / height, make sure you use floating point division not integer division.
 * \param nearClip - The minimum distance pixel can be drawn.
 * \param farClip - The maximum distance a pixel can be drawn.
 * \return A 4x4 projection matrix to be used in rendering.
 *
 */     
Matrix4x4F calculateProjectionMatrix(float fov, float aspectRatio, float nearClip, float farClip);

//Vector functions

Vector3D getInverse(Vector3D v);

Vector3F getInverse(Vector3F v);


double getMagnitude(Vector3D v);

float getMagnitude(Vector3F v);


double getDotProduct(Vector3D a, Vector3D b);

float getDotProduct(Vector3F a, Vector3F b);


Vector3D getCrossProduct(Vector3D a, Vector3D b);

Vector3F getCrossProduct(Vector3F a, Vector3F b);


Vector3D operator*(Vector3D v, double a);

Vector3F operator*(Vector3F v, float a);


Vector3D getUnitVector(Vector3D v);

Vector3F getUnitVector(Vector3F v);


//Math functions

double toRadians(double degrees);


double toDegrees(double radians);





#endif // MATHUTIL_H
