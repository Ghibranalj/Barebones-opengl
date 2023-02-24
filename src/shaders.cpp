#include <glm/gtc/type_ptr.hpp>
#define SHADERS_CPP
#include "shaders.hpp"

#include <GL/glew.h>
#include <fstream>
#include "log.hpp"
#include <regex>
#include <unordered_map>

static std::regex uniformRegex("uniform\\s+(\\w+)\\s+(\\w+);");

ShaderProgram::ShaderProgram(std::string name) {

    auto path = SHADER_PATH + name;

    std::fstream file;
    file.open(path, std::ios::in);

    if (!file.is_open()) {
        FATAL("Could not open shader file: " + path);
    }

    std::string line;
    std::string *sources = new std::string[N_SHADER_TYPES];

    ShaderType type = ShaderType::NONE;
    // std::unordered_map<std::string, bool> uniformNames;

    while (std::getline(file, line)) {
        if (line == VERTEX_HEADER) {
            type = ShaderType::VERTEX;
            continue;
        }
        if (line == FRAGMENT_HEADER) {
            type = ShaderType::FRAGMENT;
            continue;
        }
        if (line == GEOMETRY_HEADER) {
            type = ShaderType::GEOMETRY;
            continue;
        }
        if (type == ShaderType::NONE) {
            continue;
        }
        sources[(int)type] += line + "\n";

        // find uniforms
        // std::smatch match;
        // if (std::regex_search(line, match, uniformRegex)) {
        //     std::string type = match[1];
        //     std::string name = match[2];
        //     if (uniformNames.find(name) != uniformNames.end()) {
        //         continue;
        //     }
        //     uniformNames[name] = true;
        //     ShaderUniform uniform;
        //     uniform.name = name;
        //     uniform.type = type;
        //     uniforms.push_back(uniform);
        // }
    }
    this->shaderSources = sources;

    this->programID = glCreateProgram();
    for (int i = 0; i < N_SHADER_TYPES; i++) {
        if (sources[i].empty()) {
            continue;
        }
        this->shaderIDs[i] = glCreateShader(TYPE[i]);
        const char *source = this->shaderSources[i].c_str();
        glShaderSource(this->shaderIDs[i], 1, &source, NULL);
        glCompileShader(this->shaderIDs[i]);

        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(this->shaderIDs[i], GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(this->shaderIDs[i], 512, NULL, infoLog);
            FATAL("ERROR::SHADER::" + TYPE_NAME[i] + "::COMPILATION_FAILED " +
                  infoLog);
        }

        glAttachShader(this->programID, this->shaderIDs[i]);
    }

    glLinkProgram(this->programID);

}

ShaderProgram::~ShaderProgram() {


    delete[] this->shaderSources;
    glDeleteProgram(this->programID);
}

void ShaderProgram::use() {
    glUseProgram(this->programID);
}

void ShaderProgram::unuse() {
    glUseProgram(0);
}

int ShaderProgram::getUniformLocation(const std::string& name) {
    return glGetUniformLocation(this->programID, name.c_str());
}

void ShaderProgram::setUniform(int location, float value) {
    if (location == -1) {
        return;
    }
    glUniform1f(location, value);
}

void ShaderProgram::setUniform(int location, glm::vec2 &value) {
    if (location == -1) {
        return;
    }
    glUniform2f(location, value.x, value.y);
}
void ShaderProgram::setUniform(int location, glm::vec3 &value) {
    if (location == -1) {
        return;
    }
    glUniform3f(location, value.x, value.y, value.z);
}
void ShaderProgram::setUniform(int location, glm::vec4 &value) {
    if (location == -1) {
        return;
    }
    glUniform4f(location, value.x, value.y, value.z, value.w);
}
void ShaderProgram::setUniform(int location, glm::mat4 &value) {
    if (location == -1) {
        return;
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::setUniform(int location, unsigned int value) {
    if (location == -1) {
        return;
    }
    glUniform1ui(location, value);
}

void ShaderProgram::setUniform(int location, glm::uvec2 &value) {
    if (location == -1) {
        return;
    }
    glUniform2ui(location, value.x, value.y);
}

void ShaderProgram::setUniform(int location, glm::uvec3 &value) {
    if (location == -1) {
        return;
    }
    glUniform3ui(location, value.x, value.y, value.z);
}

void ShaderProgram::setUniform(int location, glm::uvec4 &value) {
    if (location == -1) {
        return;
    }
    glUniform4ui(location, value.x, value.y, value.z, value.w);
}

ShaderUniform ShaderProgram::getUniform(std::string name) {
    // for (auto uniform : this->uniforms) {
    //     if (uniform.name == name) {
    //         return uniform;
    //     }
    // }
    return ShaderUniform{"", ""};
}


void ShaderProgram::setUniform(int location, int value) {
    if (location == -1) {
        return;
    }
    glUniform1i(location, value);
}
