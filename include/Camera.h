#ifndef CAMERA_H
#define CAMERA_H

#include "MathUtil.h"

class Camera {
    public:
        
        Camera(Vector3D pos, Vector3D rot, float fieldOfVision, float aspect, float nearClipping, float farClipping);
        
        virtual ~Camera();
        
        Vector3D getPosition();
        
        Vector3D getRotation();
        
        void setPosition(Vector3D);
        
        void setRotation(Vector3D);
        
        void setFov(float newFov);
        
        void setAspectRatio(float newAspectRatio);
        
        void setClipping(float newNearClip, float newFarClip);
        
        void shiftPosition(Vector3D);
        
        void shiftRotation(Vector3D);
        
        Matrix4x4F getViewMatrix();
        
        Matrix4x4F getProjMatrix();
        
    protected:
        
    private:
        
        Matrix4x4F viewMatrix;
        
        Matrix4x4F projMatrix;
        
        Vector3D position;
        
        Vector3D rotation; //each coord represents rotation about that axis
        
        float fov;
        
        float aspectRatio;
        
        float nearClip;
        
        float farClip;
        
};

#endif // CAMERA_H
