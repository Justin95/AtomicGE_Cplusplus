#include "Renderer.h"
#include "ShaderProgram.h"
#include "Renderable.h"
#include <vector>

#include <stdlib.h>


int main(){
    Camera cam({0,0,0}, {0,0,0}, 90.0, 0, .1, 1000.0); //aspect ratio auto initialized
    Renderer render(&cam);
    render.initialize("AtomicGE Test", false, 0);
    
    
    float pos[] = {-1,0,-5, 1,0,-5, 0,1,-5};
    float texCoords[] = {0,0, 0,0, 0,0};
    float color[] = {1,0,0,0, 0,1,0,0, 0,0,1,0};
    unsigned int indices[] = {0,1,2, 2,1,0};
    
    VertexBufferObject position         (9 , &pos      , 9*sizeof(float)       , POSITION_INDEX      , GL_FLOAT, GL_ARRAY_BUFFER, 3);
    VertexBufferObject texCoordsbuffer  (6 , &texCoords, 6*sizeof(float)       , TEXTURE_COORDS_INDEX, GL_FLOAT, GL_ARRAY_BUFFER, 2);
    VertexBufferObject colorbuffer      (12, &color    ,12*sizeof(float)       , COLOR_INDEX         , GL_FLOAT, GL_ARRAY_BUFFER, 4);
    VertexBufferObject indicesbuffer    (6 , &indices  , 6*sizeof(unsigned int), POSITION_INDEX      , GL_UNSIGNED_INT, GL_ELEMENT_ARRAY_BUFFER, 1);
    
    
    std::vector<VertexBufferObject*> vbos;
    vbos.push_back(&position);
    vbos.push_back(&texCoordsbuffer);
    vbos.push_back(&colorbuffer);
    vbos.push_back(&indicesbuffer);
    
    VertexArrayObject vao(vbos);
    
    Shader vertex("Shaders\\defaultVertexShader.vs");
    Shader fragment("Shaders\\defaultFragmentShader.fs");
    
    vertex.uploadShader();
    fragment.uploadShader();
    
    ShaderProgram program(&vertex, &fragment);
    program.linkShaderProgram();
    
    Model model(&vao);
    model.sendToGPU();
    
    Renderable test(&model, &program, (Vector3D){0.0,0.0,-10.0}, (Vector3D){0.0,0.0,0.0});
    
    render.addRenderable(&test);

    render.renderLoop();
}
