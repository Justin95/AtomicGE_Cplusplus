#include "VertexArrayObject.h"

#include <iostream>

VertexArrayObject::VertexArrayObject(std::vector<VertexBufferObject*> bufferObjects){
    numIndices = 0;
    for(VertexBufferObject* buffer : bufferObjects){
        if(buffer->getUsage() != GL_ELEMENT_ARRAY_BUFFER){
            vbos.push_back(buffer);
            continue;
        }
        numIndices = buffer->getNumElements();
        indicesBuffer = buffer;
    }
}

VertexArrayObject::~VertexArrayObject() {
    for(VertexBufferObject* vbo : vbos){
        delete vbo;
    }
    glDeleteVertexArrays(1, &vaoID);
}


void VertexArrayObject::prepareBuffers(){
    glBindVertexArray(vaoID);
    //prepare vbos
    indicesBuffer->prepareBuffer();
    for(VertexBufferObject* buffer : vbos){
        buffer->prepareBuffer();
    }
    glBindVertexArray(0);
}

void VertexArrayObject::uploadToGPU(){
    glGenVertexArrays(1, &vaoID);
    for(VertexBufferObject* vbo : vbos){
        vbo->sendBufferToGPU();
    }
    indicesBuffer->sendBufferToGPU();
}

void VertexArrayObject::bindVAO(){
    glBindVertexArray(vaoID);
}

void VertexArrayObject::unbindVAO(){
    glBindVertexArray(0);
}


int VertexArrayObject::getNumIndices(){
    return numIndices;
}

void VertexArrayObject::bindIndicesBuffer(){
    indicesBuffer->prepareBuffer();
}

VertexBufferObject* VertexArrayObject::getIndicesBuffer(){
    return indicesBuffer;
}

