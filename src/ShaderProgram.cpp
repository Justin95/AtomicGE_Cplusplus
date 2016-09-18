#include "ShaderProgram.h"

#include <stdlib.h>
#include <iostream>

ShaderProgram::ShaderProgram(Shader* vertexShader, Shader* fragmentShader) {
    this->vertexShader = vertexShader;
    this->fragmentShader = fragmentShader;
}

ShaderProgram::~ShaderProgram() {
    glDetachShader(shaderProgramID, vertexShader->getShaderID());
    glDetachShader(shaderProgramID, fragmentShader->getShaderID());
}


int ShaderProgram::linkShaderProgram(){
    this->shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertexShader->getShaderID());
    glAttachShader(shaderProgramID, fragmentShader->getShaderID());
    glLinkProgram(shaderProgramID);
    GLint result = -1;
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &result);
    if(result == GL_FALSE){
        GLint logSize = 0;
        glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &logSize);
        char* infoLog = (char*) malloc(sizeof(char) * logSize);
        glGetProgramInfoLog(shaderProgramID, logSize, NULL, infoLog);
        std::cerr << "OpenGL Shader Program Linking Failure InfoLog: \n\n" << infoLog << "\n\n" << std::endl;
        free(infoLog);
        glDeleteProgram(shaderProgramID);
        glDetachShader(shaderProgramID, vertexShader->getShaderID());
        glDetachShader(shaderProgramID, fragmentShader->getShaderID());
        return -1;
    }
    return 0;
}


void ShaderProgram::setUniform(const char* uniformName, Matrix4x4F matrix){
    glUseProgram(shaderProgramID);
    GLint loc = glGetUniformLocation(shaderProgramID, uniformName);
    glUniformMatrix4fv(loc, 1, GL_TRUE, (const float*) &matrix);
    glUseProgram(0);
}


void ShaderProgram::setUniform(const char* uniformName, Vector3F v){
    glUseProgram(shaderProgramID);
    GLint loc = glGetUniformLocation(shaderProgramID, uniformName);
    glUniform3f(loc, v.x, v.y, v.z);
    glUseProgram(0);
}


void ShaderProgram::bindShader(){
    glUseProgram(shaderProgramID);
}


void ShaderProgram::unbindShader(){
    glUseProgram(0);
}

