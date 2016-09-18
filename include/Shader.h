#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

class Shader {
    public:
        
        Shader(std::string filePath);
        
        virtual ~Shader();
        
        int uploadShader();
        
        GLuint getShaderID();
        
    protected:
        
    private:
        
        GLuint shaderID;
        
        GLuint shaderType;
        
        std::string filePath;
        
        void readSource(char*** source, int* length);
        
        int calcShaderType();
        
};

#endif // SHADER_H
