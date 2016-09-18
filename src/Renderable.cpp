#include "Renderable.h"

#include <iostream>

Renderable::Renderable(Model* m, ShaderProgram* shaderToUse, Vector3D pos, Vector3D rot){
    model = m;
    shader = shaderToUse;
    position = pos;
    rotation = rot;
}


Renderable::~Renderable(){
    
}


bool Renderable::isOpaque(){
    return true; //temp
}


void Renderable::draw(){
    VertexArrayObject* vao = model->getVertexArrayObject();
    shader->setUniform("model", calculateModelMatrix(position, rotation, 1));
    shader->bindShader();
    vao->bindVAO();
    GLuint dataType = vao->getIndicesBuffer()->getDataType();
    glDrawElements(GL_TRIANGLES, vao->getNumIndices(), dataType, 0);
    shader->unbindShader();
    vao->unbindVAO();
    //note: on nvidia cards if no shader program is active, white triangle is drawn in screen space
}


void Renderable::setShader(ShaderProgram* newShader){
    shader = newShader;
}


void Renderable::setPosition(Vector3D v){
    position = v;
}


void Renderable::setRotation(Vector3D v){
    rotation = v;
}


ShaderProgram* Renderable::getShaderProgram(){
    return shader;
}
