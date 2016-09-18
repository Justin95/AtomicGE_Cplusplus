#include "Shader.h"

#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>

#define VERTEX_SHADER_EXT    ".vs"
#define FRAGMENT_SHDAER_EXT  ".fs"
#define GEOMETRY_SHADER_EXT  ".gs"

Shader::Shader(std::string filePath) {
    this->filePath = filePath;
    this->shaderType = calcShaderType();
}

Shader::~Shader() {
    
}


int Shader::uploadShader(){
    this->shaderID = glCreateShader(shaderType);
    char** source = NULL;
    int length;
    readSource(&source, &length);
    glShaderSource(shaderID, length, source, NULL);
    glCompileShader(shaderID);
    for(int i = 0; i < length; i++){
        free(source[i]);
    }
    free(source);
    GLint result = -1;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE){
        char test[512];
        glGetShaderSource(shaderID, 512, NULL, test);
        std::cerr << test << "\n" << std::endl;
        GLint logSize = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logSize); 
        char* infoLog = (char*) malloc(sizeof(char) * logSize);
        glGetShaderInfoLog(shaderID, logSize, NULL, infoLog);
        std::cerr << "OpenGL Shader Compile Failure InfoLog: \n\n" << infoLog << "\n\n" << std::endl;
        free(infoLog);
        return -1;
    }
    return 0;
}


void Shader::readSource(char*** source, int* length){
    std::ifstream shaderFile;
    shaderFile.open(this->filePath);
    if(!shaderFile.is_open()){
        std::cerr<<"Shader File not found!"<<std::endl;
    }
    std::vector<std::string> lines;
    std::string line;
    while(std::getline(shaderFile, line)){
        line.append("\n"); //newlines very important or comments in shader will extend forever
        lines.push_back(line);
    }
    *length = lines.size();
    *source = (char**) malloc(sizeof(char*) * lines.size());
    for(unsigned int i = 0; i < lines.size(); i++){
        line = lines.at(i);
        (*source)[i] = (char*) malloc(sizeof(char) * line.length() + 1); //+1 for null terminator
        const char* cString = line.c_str();
        strcpy((*source)[i], cString);
    }
    shaderFile.close();
}


int Shader::calcShaderType(){
    std::string ext = this->filePath.substr(filePath.size() - 3, std::string::npos); //read last 3 chars of string
    if(ext == VERTEX_SHADER_EXT){
        return GL_VERTEX_SHADER;
    }else if(ext == FRAGMENT_SHDAER_EXT){
        return GL_FRAGMENT_SHADER;
    }else if(ext == GEOMETRY_SHADER_EXT){
        return GL_GEOMETRY_SHADER;
    }
    std::cerr << "INVALID SHADER TYPE! bad extension." << std::endl;
    return -1;
}


GLuint Shader::getShaderID(){
    return this->shaderID;
}
