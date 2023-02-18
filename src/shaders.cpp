#include "shaders.hpp"

#include <GL/glew.h>
#include <fstream>
#include "log.hpp"


ShaderProgram::ShaderProgram(std::string name){

    auto path = SHADER_PATH + name;

    std::fstream file;
    file.open(path, std::ios::in);


    if (!file.is_open()){
        FATAL("Could not open shader file: " + path);
    }


    std::string line;
    std::string * sources = new std::string[2];


    ShaderType type = ShaderType::NONE;

    while(std::getline(file, line)){
        if(line == VERTEX_HEADER){
            type = ShaderType::VERTEX;
            continue;
        }
        if(line == FRAGMENT_HEADER){
            type = ShaderType::FRAGMENT;
            continue;
        }
        if (type == ShaderType::NONE){
            continue;
        }
        sources[(int)type] += line + "\n";
    }
    this->shaderSources = sources;


    this->programID = glCreateProgram();

    unsigned int TYPE[2] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
    std::string TYPE_NAME[2] = {"VERTEX", "FRAGMENT"};
    for (int i = 0 ; i < 2 ; i++){
        this->shaderIDs[i] = glCreateShader(TYPE[i]);
        const char * source = this->shaderSources[i].c_str();
        glShaderSource(this->shaderIDs[i], 1, &source, NULL);
        glCompileShader(this->shaderIDs[i]);

        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(this->shaderIDs[i], GL_COMPILE_STATUS, &success);

        if(!success)
        {
            glGetShaderInfoLog(this->shaderIDs[i], 512, NULL, infoLog);
            FATAL("ERROR::SHADER::" + TYPE_NAME[i] + "::COMPILATION_FAILED " + infoLog);
        }

        // attach shader to program
        glAttachShader(this->programID, this->shaderIDs[i]);
    }

    glLinkProgram(this->programID);
}


ShaderProgram::~ShaderProgram(){
    delete[] this->shaderSources;
    glDeleteProgram(this->programID);
}


void ShaderProgram::use(){
    glUseProgram(this->programID);
}

void ShaderProgram::unuse(){
    glUseProgram(0);
}
