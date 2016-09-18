#ifndef MODEL_H
#define MODEL_H

#include "VertexArrayObject.h"

class Model {
    public:
        
        Model(VertexArrayObject*);
        
        virtual ~Model();
        
        VertexArrayObject* getVertexArrayObject();
        
        void sendToGPU();
        
        void setClickCallBack(void* func);
        
        //updateAnimation(int time);
        
        void clicked();
        
    protected:
        
    private:
        
        VertexArrayObject* vao;
        
        void* clickCallBack;
        
        //ClickBox* box;
        
};

#endif // MODEL_H
