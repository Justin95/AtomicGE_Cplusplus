#include "VertexBufferObject.h"

#include <iostream>
#include <stdlib.h>


VertexBufferObject::VertexBufferObject(int numberOfElements, void* elements, int bufferSize, int shaderLayoutLocation,
                                             GLuint glType, GLuint bufferUsage, int elemPerVertex){
    
    if(numberOfElements < 0){
        std::cerr << "Cannot form VBO with less than 0 elements!" << std::endl;
        return;
    }
    if(glType != GL_FLOAT && glType != GL_UNSIGNED_SHORT && glType != GL_UNSIGNED_INT){
        std::cerr << "INVALID VBO TYPE!" << std::endl;
        return;
    }
    if(!(bufferUsage == GL_ARRAY_BUFFER || bufferUsage == GL_ELEMENT_ARRAY_BUFFER)){
        std::cerr << "Invalid buffer usage!" << std::endl;
        return;
    }
    int elementSize = bufferSize / numberOfElements;
    
    numElements = numberOfElements;
    buffer = malloc(bufferSize);
    copyBuffer(elements, buffer, elementSize, numElements);
    
    layoutLocation = shaderLayoutLocation;
    dataType = glType;
    usage = bufferUsage;
    elementsPerVertex = elemPerVertex;
    glGenBuffers(1, &vboID);
}


void VertexBufferObject::copyBuffer(void* from, void* to, int elementSize, int numberOfElements){
    for(int i = 0; i < elementSize * numberOfElements; i++){
        ((char*) to)[i] = ((char*) from)[i]; //watch this for potential side effects
    }
}


VertexBufferObject::~VertexBufferObject(){
    free(buffer);
    //free gpu memory
    //free the openGL id for this vbo
    freeGPUBuffer();
}


void VertexBufferObject::sendBufferToGPU(){ 
    int elementSize = dataType == GL_UNSIGNED_SHORT ? 2 : 4;
    glBindBuffer(usage, vboID);//usage: GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER
    glBufferData(usage, numElements * elementSize, buffer, GL_STATIC_DRAW);
    glBindBuffer(usage, 0);
}



void VertexBufferObject::freeGPUBuffer(){
    glDeleteBuffers(1, &vboID);
}





void VertexBufferObject::prepareBuffer(){
    glBindBuffer(usage, vboID);
    if(usage == GL_ELEMENT_ARRAY_BUFFER) return;
    glVertexAttribPointer(layoutLocation, elementsPerVertex, dataType, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(layoutLocation);
}


GLuint VertexBufferObject::getUsage(){
    return usage;
}


int VertexBufferObject::getNumElements(){
    return numElements;
}


void* VertexBufferObject::getBuffer(){
    return buffer;
}


GLuint VertexBufferObject::getDataType(){
    return dataType;
}
