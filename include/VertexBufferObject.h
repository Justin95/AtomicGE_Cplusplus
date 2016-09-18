#ifndef VERTEXBUFFEROBJECT_H
#define VERTEXBUFFEROBJECT_H

#include "GL/glew.h"
#include <GLFW/glfw3.h>

class VertexBufferObject {
    public:
        
        VertexBufferObject(int numberOfElements, void* elements, int bufferSize, int shaderLayoutLocation,
                            GLuint glType, GLuint usage, int elemPerVertex);
        
        virtual ~VertexBufferObject();
        
        void sendBufferToGPU();
        
        //void modifyBuffer(VBOModifier); //implement later
        
        GLuint getVboID();
        
        GLuint getDataType();
        
        GLuint getUsage();
        
        int getElementsPerVertex();
        
        int getLayoutLocation();
        
        int getNumElements();
        
        void prepareBuffer();
        
        void* getBuffer();
        
        
    protected:
        
    private:
        
        GLuint vboID;
        
        GLuint dataType;
        
        GLuint usage; //GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER
        
        int elementsPerVertex;
        
        int layoutLocation;
        
        void* buffer; //it was this or make a template and cram all the code into this .h file, this is actually less code/ simpler
        
        int numElements;
        
        void freeGPUBuffer();
        
        void copyBuffer(void* from, void* to, int elementSize, int numberOfElements);
        
};

#endif // VERTEXBUFFEROBJECT_H
