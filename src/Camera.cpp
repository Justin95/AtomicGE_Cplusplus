#include "Camera.h"

Camera::Camera(Vector3D pos, Vector3D rot, float fieldOfVision, float aspect, float nearClipping, float farClipping) {
    position = pos;
    rotation = rot;
    fov = fieldOfVision;
    aspectRatio = aspect;
    nearClip = nearClipping;
    farClip = farClipping;
    viewMatrix = calculateViewMatrix(position, rotation);
    projMatrix = calculateProjectionMatrix(fov, aspectRatio, nearClip, farClip);
}

Camera::~Camera() {
    
}


Vector3D Camera::getPosition(){
    return position;
}


Vector3D Camera::getRotation(){
    return rotation;
}


void Camera::setPosition(Vector3D pos){
    position = pos;
    viewMatrix = calculateViewMatrix(position, rotation);
}


void Camera::setRotation(Vector3D rot){
    rotation = rot;
    viewMatrix = calculateViewMatrix(position, rotation);
}


void Camera::shiftPosition(Vector3D shift){
    position.x += shift.x;
    position.y += shift.y;
    position.z += shift.z;
    viewMatrix = calculateViewMatrix(position, rotation);
}


void Camera::shiftRotation(Vector3D shift){
    rotation.x += shift.x;
    rotation.y += shift.y;
    rotation.z += shift.z;
    viewMatrix = calculateViewMatrix(position, rotation);
}


Matrix4x4F Camera::getViewMatrix(){
    return viewMatrix;
}


void Camera::setFov(float newFov){
    fov = newFov;
    projMatrix = calculateProjectionMatrix(fov, aspectRatio, nearClip, farClip);
}
        
void Camera::setAspectRatio(float newAspectRatio){
    aspectRatio = newAspectRatio;
    projMatrix = calculateProjectionMatrix(fov, aspectRatio, nearClip, farClip);
}
        
void Camera::setClipping(float newNearClip, float newFarClip){
    nearClip = newNearClip;
    farClip = newFarClip;
    projMatrix = calculateProjectionMatrix(fov, aspectRatio, nearClip, farClip);
}

Matrix4x4F Camera::getProjMatrix(){
    return projMatrix;
}


