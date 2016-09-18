#include "Renderer.h"

#include <iostream>

Renderer::Renderer(Camera* cam) {
    inputCollector = NULL;
    camera = cam;
}

Renderer::~Renderer() {
    delete inputCollector;
}


int Renderer::initialize(const char* title, bool fullScreen, int refreshRate){
    if(!glfwInit()){
            std::cerr << "GLFW initialization failed" << std::endl;
            return -1;
    }
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor()); //currently only single monitor support
    this->targetFrameRate = refreshRate;//-1 unlimited, 0 monitor refresh rate
    GLFWmonitor* monitor = fullScreen ? glfwGetPrimaryMonitor() : NULL; //if null full screen not used
    this->window = glfwCreateWindow(mode->width, mode->height, title, monitor, NULL);
    camera->setAspectRatio((float)mode->width / (float)mode->height);
    if(window == NULL){
        glfwTerminate();
        std::cerr << "Window initialization failed" << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    GLenum result = glewInit();
    if(result != GLEW_OK){
        std::cerr << "GLEW Error: " << glewGetErrorString(result) << std::endl;
        return -1;
    }
    inputCollector = new InputCollector(window);
    this->keepRunning = true;
    printRenderReport();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    return 0;
}


void Renderer::renderLoop(){
    
    while(this->keepRunning){
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        checkError();
        
        renderFrame();
        
        glfwSwapBuffers(window);
        
        glfwPollEvents();
        inputCollector->collectInput();
        
        if(glfwWindowShouldClose(window)){
            keepRunning = false;
        }
    }
    
    glfwTerminate();
}


void Renderer::renderFrame(){
    Matrix4x4F viewMatrix = camera->getViewMatrix();
    Matrix4x4F projMatrix = camera->getProjMatrix();
    for(unsigned int i = 0; i < shaderList.size(); i++){
        shaderList.at(i)->setUniform("view", viewMatrix); //must set the matrices for every used shader program
        shaderList.at(i)->setUniform("projection", projMatrix); //this doesn't have to be every frame just when updated
    }
    while(toRender.hasNext()){
        toRender.getNext()->draw();
    }
    toRender.reset();
}


void Renderer::printRenderReport(){
    std::cerr << "openGL version:           " << glGetString(GL_VERSION)  << std::endl;
    std::cerr << "openGL renderer:          " << glGetString(GL_RENDERER) << std::endl;
    std::cerr << "openGL vendor:            " << glGetString(GL_VENDOR)   << std::endl;
    std::cerr << "shading language version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}


void Renderer::setFullScreen(bool fullScreen){
    GLFWmonitor* monitor = fullScreen ? glfwGetPrimaryMonitor() : NULL;
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int refreshRate = targetFrameRate == 0 ? mode->refreshRate : targetFrameRate; //TODO: add support for unlimited with -1
    glfwSetWindowMonitor(this->window, monitor, 0, 0, mode->width, mode->height, refreshRate);
}


void Renderer::addRenderable(Renderable* renderable){
    this->shaderList.push_back(renderable->getShaderProgram());
    this->toRender.addRenderable(renderable);
}

void Renderer::removeRenderable(Renderable* renderable){
    this->toRender.removeRenderable(renderable);
}



void Renderer::checkError(){
    GLenum err = GL_NO_ERROR;
    while((err = glGetError()) != GL_NO_ERROR){
        std::cerr << "GL error: " << err << std::endl;
    }
}



InputCollector* Renderer::getInputCollector(){
    return inputCollector;
}

