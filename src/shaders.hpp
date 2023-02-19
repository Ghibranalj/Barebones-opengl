#ifndef SHADERS_H_
#define SHADERS_H_
#include "interface.hpp"
#include <iostream>
#include <string>
#include <GL/glew.h>

#ifndef SHADER_PATH
#define SHADER_PATH "res/shaders/"
#endif

#define VERTEX_HEADER "#VERTEX"
#define FRAGMENT_HEADER "#FRAGMENT"
#define GEOMETRY_HEADER "#GEOMETRY"

#define N_SHADER_TYPES 3
#ifdef SHADERS_CPP
static unsigned int TYPE[N_SHADER_TYPES] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER};
static std::string TYPE_NAME[N_SHADER_TYPES] = {"VERTEX", "FRAGMENT", "GEOMETRY"};
enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 , GEOMETRY = 2};
#endif // SHADERS_CPP

class ShaderProgram {
  public:
    ShaderProgram(std::string shaderName);
    ~ShaderProgram();

    void use();
    void unuse();

    int getUniformLocation(std::string uniformName);
    void setUniformFloat(int location, float value);
    void setUniformUint(int location, unsigned int value);

    inline void printShaderSources() {
        std::cout << "Vertex Shader Source:" << this->shaderSources[0]
                  << std::endl;
        std::cout << "Fragment Shader Source:" << this->shaderSources[1]
                  << std::endl;
    }

    void bindUniform();

  private:
    unsigned int programID;
    unsigned int shaderIDs[N_SHADER_TYPES];
    std::string *shaderSources;
};

#endif // SHADERS_H_
