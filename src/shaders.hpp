#ifndef SHADERS_H_
#define SHADERS_H_
#include "log.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

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

struct ShaderUniform {
    std::string name;
    std::string type;
};

class ShaderProgram {
  public:
    ShaderProgram(std::string shaderName);
    ~ShaderProgram();
    void use();
    void unuse();

    int getUniformLocation(const std::string &uniformName);
    void setUniform(int location, float value);
    void setUniform(int location, glm::vec2 &value);
    void setUniform(int location, glm::vec3 &value);
    void setUniform(int location, glm::vec4 &value);
    void setUniform(int location, glm::mat4 &value);
    void setUniform(std::string uniformName, float value) {
        setUniform(getUniformLocation(uniformName), value);
    }
    void setUniform(std::string uniformName, glm::vec2 &value) {
        setUniform(getUniformLocation(uniformName), value);
    }
    void setUniform(std::string uniformName, glm::vec3 &value) {
        setUniform(getUniformLocation(uniformName), value);
    }
    void setUniform(std::string uniformName, glm::vec4 &value) {
        setUniform(getUniformLocation(uniformName), value);
    }
    void setUniform(std::string uniformName, glm::mat4 &value) {
        setUniform(getUniformLocation(uniformName), value);
    }

    void setUniform(int location, unsigned int value);
    void setUniform(int location, glm::uvec2 &value);
    void setUniform(int location, glm::uvec3 &value);
    void setUniform(int location, glm::uvec4 &value);
    void setUniform(std::string uniformName, unsigned int value) {
        setUniform(getUniformLocation(uniformName), value);
    }
    void setUniform(std::string uniformName, glm::uvec2 &value) {
        setUniform(getUniformLocation(uniformName), value);
    }
    void setUniform(std::string uniformName, glm::uvec3 &value) {
        setUniform(getUniformLocation(uniformName), value);
    }
    void setUniform(std::string uniformName, glm::uvec4 &value) {
        setUniform(getUniformLocation(uniformName), value);
    }

    void setUniform(int location, int value);

    // static

    ShaderUniform getUniform(std::string uniformName);

  private:
    unsigned int programID;
    unsigned int shaderIDs[N_SHADER_TYPES];
    std::string *shaderSources;
    // std::vector<ShaderUniform> uniforms;
};

#endif // SHADERS_H_
