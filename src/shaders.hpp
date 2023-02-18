#ifndef SHADERS_H_
#define SHADERS_H_
#include "interface.hpp"
#include <iostream>
#include <string>

#ifndef SHADER_PATH
#define SHADER_PATH "res/shaders/"
#endif

#define VERTEX_HEADER "#VERTEX"
#define FRAGMENT_HEADER "#FRAGMENT"

enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };

class ShaderProgram {
  public:
    ShaderProgram(std::string shaderName);
    ~ShaderProgram();

    void use();
    void unuse();

    inline void printShaderSources() {

        std::cout << "Vertex Shader Source:" << this->shaderSources[0]
                  << std::endl;
        std::cout << "Fragment Shader Source:" << this->shaderSources[1]
                  << std::endl;
    }

  private:
    unsigned int programID;
    unsigned int shaderIDs[2];
    std::string *shaderSources;
};

#endif // SHADERS_H_
