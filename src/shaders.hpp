#ifndef SHADERS_H_
#define SHADERS_H_
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <string>

#ifndef SHADER_PATH
#define SHADER_PATH "res/shaders/"
#endif

#define VERTEX_HEADER "#VERTEX"
#define FRAGMENT_HEADER "#FRAGMENT"
#define GEOMETRY_HEADER "#GEOMETRY"

#define N_SHADER_TYPES 3
#ifdef SHADERS_CPP
static unsigned int TYPE[N_SHADER_TYPES] = {
    GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER};
static std::string TYPE_NAME[N_SHADER_TYPES] = {"VERTEX", "FRAGMENT",
                                                "GEOMETRY"};
enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1, GEOMETRY = 2 };
#endif // SHADERS_CPP

class ShaderProgram {
  public:
    ShaderProgram(std::string shaderName);
    ~ShaderProgram();

    void use();
    void unuse();

    int getUniformLocation(std::string uniformName);
    void setUniformF(int location, float value);
    void setUniform2F(int location, glm::vec2 &value);
    void setUniform3F(int location, glm::vec3 &value);
    void setUniform4F(int location, glm::vec4 &value);
    void setUniformM4F(int location, glm::mat4 &value);

    void setUniformF(std::string uniformName, float value) {
        setUniformF(getUniformLocation(uniformName), value);
    }
    void setUniform2F(std::string uniformName, glm::vec2 &value) {
        setUniform2F(getUniformLocation(uniformName), value);
    }
    void setUniform3F(std::string uniformName, glm::vec3 &value) {
        setUniform3F(getUniformLocation(uniformName), value);
    }
    void setUniform4F(std::string uniformName, glm::vec4 &value) {
        setUniform4F(getUniformLocation(uniformName), value);
    }
    void setUniformM4F(std::string uniformName, glm::mat4 &value) {
        setUniformM4F(getUniformLocation(uniformName), value);
    }

    void setUniformUI(int location, unsigned int value);
    void setUniform2UI(int location, glm::uvec2 &value);
    void setUniform3UI(int location, glm::uvec3 &value);
    void setUniform4UI(int location, glm::uvec4 &value);

    void setUniformUI(std::string uniformName, unsigned int value) {
        setUniformUI(getUniformLocation(uniformName), value);
    }
    void setUniform2UI(std::string uniformName, glm::uvec2 &value) {
        setUniform2UI(getUniformLocation(uniformName), value);
    }
    void setUniform3UI(std::string uniformName, glm::uvec3 &value) {
        setUniform3UI(getUniformLocation(uniformName), value);
    }
    void setUniform4UI(std::string uniformName, glm::uvec4 &value) {
        setUniform4UI(getUniformLocation(uniformName), value);
    }

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
