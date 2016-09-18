#ifndef RENDERABLE_H
#define RENDERABLE_H


#include "VertexArrayObject.h"
#include "MathUtil.h"
#include "ShaderProgram.h"
#include "Model.h"


class Renderable {
    public:
        
        Renderable(Model*, ShaderProgram*, Vector3D, Vector3D);
        
        virtual ~Renderable();
        
        virtual bool isOpaque();
        
        virtual void draw();
        
        void setShader(ShaderProgram*);
        
        void setPosition(Vector3D);
        
        void setRotation(Vector3D);
        
        ShaderProgram* getShaderProgram();

    protected:

    private:
        
        Model* model;
        
        ShaderProgram* shader;
        
        Vector3D position;
        
        Vector3D rotation;
        
};

#endif // RENDERABLE_H
