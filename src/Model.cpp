#include "Model.h"

Model::Model(VertexArrayObject* modelVAO){
    vao = modelVAO;
}

Model::~Model(){
    
}


VertexArrayObject* Model::getVertexArrayObject(){
    return vao;
}


void Model::sendToGPU(){
    vao->uploadToGPU();
    vao->prepareBuffers();
}


void Model::setClickCallBack(void* func){
    clickCallBack = func;
}


void Model::clicked(){
    if(clickCallBack == NULL) return;
    ((void(*)(/*Function argument list here*/))clickCallBack)();
}
