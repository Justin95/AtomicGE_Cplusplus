#ifndef INPUTCOLLECTOR_H
#define INPUTCOLLECTOR_H

#include <stdlib.h>
#include <GLFW/glfw3.h>


class InputCollector { //http://www.glfw.org/docs/latest/input_guide.html
    public:
        
        InputCollector(GLFWwindow* win);
        
        virtual ~InputCollector();
        
        /** \brief Collects the input from the window since the last time this function was called.
         *  Also updates any queued mouse image changes.
         */                                                     
        void collectInput();
        
        /** \brief Sets a function to be called to process a key press. That function will be called as:
         *  keyFunction(GLFWwindow* window, int key, int scancode, int action, int mods)
         *
         * \param keyFunction a pointer to the function to be set as the callback function
         */                                                     
        void setCallback(void* keyFunction); //including mouse callback
        
        /** \brief This function sets the mouse cursor for the program's window to use. 
        *
        * \param height The height of the new cursor image
        * \param width The width of the new cursor image
        * \param pixels The new cursor image
        * \param xShift The right shift of the cursor center from the top left of the image
        * \param yShift The down shift of the cursor center from the top left of the image
        */ 
        void setMouseCursor(int height, int width, int* pixels, int xShift, int yShift);
        
    protected:
        
    private:
        
        GLFWwindow* window;
        
        GLFWcursor* mouse;
        
        void updateCursor();
        
        typedef struct CursorImage {
            GLFWimage* image;
            int xShift;
            int yShift;
        }CursorImage;
        
        CursorImage* newCursor;
};

#endif // INPUTCOLLECTOR_H
