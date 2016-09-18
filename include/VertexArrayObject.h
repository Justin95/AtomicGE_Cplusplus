#ifndef VERTEXARRAYOBJECT_H
#define VERTEXARRAYOBJECT_H

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <vector>

#include "ShaderProgram.h"
#include "VertexBufferObject.h"

class VertexArrayObject {
    public:
        
        //VertexBufferObjects should NOT be shared between different VertexArrayObjects
        VertexArrayObject(std::vector<VertexBufferObject*> bufferObjects);
        
        virtual ~VertexArrayObject();
        
        void prepareBuffers();
        
        void bindVAO();
        
        void unbindVAO();
        
        int getNumIndices(); //should move this into a model class
        
        void bindIndicesBuffer();
        
        VertexBufferObject* getIndicesBuffer();
        
        void uploadToGPU();
        
    protected:
        
    private:
        
        GLuint vaoID;
        
        int numIndices; 
        
        VertexBufferObject* indicesBuffer;
        
        std::vector<VertexBufferObject*> vbos;
        
};

#endif // VERTEXARRAYOBJECT_H
