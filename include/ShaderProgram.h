#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "Shader.h"
#include "MathUtil.h"

#define POSITION_INDEX       0
#define TEXTURE_COORDS_INDEX 1
#define COLOR_INDEX          2
#define NORMAL_INDEX         3


class ShaderProgram { //note may implement seperable programs and program pipelines later
    public:
        
        ShaderProgram(Shader* vertexShader, Shader* fragmentShader);
        
        virtual ~ShaderProgram();
        
        int linkShaderProgram();
        
        void setUniform(const char* uniformName, Matrix4x4F matrix);
        
        void setUniform(const char* uniformName, Vector3F v);
        
        void bindShader();
        
        void unbindShader();
        
    protected:
        
    private:
        
        Shader* vertexShader;
        
        Shader* fragmentShader;
        
        GLuint shaderProgramID;
        
};

#endif // SHADERPROGRAM_H
