#include "InputCollector.h"

InputCollector::InputCollector(GLFWwindow* win){
    window = win;
}

InputCollector::~InputCollector(){
    
}


void InputCollector::collectInput(){
    glfwPollEvents();
    updateCursor();
}


void InputCollector::setCallback(void* func){
    glfwSetKeyCallback(window,  (GLFWkeyfun) func);
}

    
void InputCollector::setMouseCursor(int height, int width, int* pixels, int xShift, int yShift){
    if(newCursor != NULL){
        delete newCursor->image;
        free(newCursor);
    }
    newCursor = (CursorImage*) malloc(sizeof(CursorImage));
    GLFWimage* image = new GLFWimage();
    image->height = height;
    image->width = width;
    image->pixels = (unsigned char*) pixels;
    newCursor->xShift = xShift;
    newCursor->yShift = yShift;
    newCursor->image = image;
}


void InputCollector::updateCursor(){
    if(newCursor == NULL) return;
    if(mouse != NULL){
        glfwDestroyCursor(mouse);
    }
    mouse = glfwCreateCursor(newCursor->image, newCursor->xShift, newCursor->yShift);
    delete newCursor->image;
    free(newCursor);
    newCursor = NULL;
}
