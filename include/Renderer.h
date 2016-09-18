#ifndef RENDERER_H
#define RENDERER_H

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "RenderList.h"
#include "InputCollector.h"
#include "Camera.h"

class Renderer {
    
    public:
        
        Renderer(Camera* cam);
        
        virtual ~Renderer();
        
        /** \brief This function initializes the glfwWindow and loads openGL functions.
         *
         * \param title The window title
         * \param fullScreen whether the window should be made full screen
         * \param refreshRate the target refresh rate of the window, -1 for unlimited, 0 for vsync
         */
        int initialize(const char* title, bool fullScreen, int refreshRate);
        
        /** \brief The main rendering loop for the engine. This function will only return once shutdown
         *  begins.
         */
        void renderLoop();
        
        /** \brief Changes whether the window is in full screen or not.
         *
         * \param fullScreen whether the window should now be full screen
         */
        void setFullScreen(bool fullScreen);
        
        /** \brief This function adds a Renderable object to the list of Renerables drawn each frame.
         *
         * \param Renderable the renderable to add
         */
        void addRenderable(Renderable*);
        
        /** \brief This function removes a Renderable object from the list of Renderables drawn each frame.
         *
         * \param Renderable the renderable to remove
         */
        void removeRenderable(Renderable*);
        
        /** \brief This function sets the camera object used for viewing.
         *
         * \param Camera the camera to use
         */
        void setCamera(Camera* camera);
        
        /** \brief This function gets the InputCollector object used to get input from the window.
         *
         * \return the InputCollector object associated with this window.
         */
        InputCollector* getInputCollector();

    protected:
        

    private:
        GLFWwindow* window;
        
        Camera* camera;
        
        RenderList toRender;
        
        InputCollector* inputCollector;
        
        bool keepRunning;
        
        int targetFrameRate;
        
        void renderFrame();
        
        void printRenderReport();
        
        void checkError();
        
        std::vector<ShaderProgram*> shaderList;
        
};

#endif // RENDERER_H
