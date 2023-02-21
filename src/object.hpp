#ifndef OBJECT_H_
#define OBJECT_H_

#include <string>
#include <memory>
#include "VAO.hpp"
#include "VBO.hpp"
#include "shaders.hpp"
#include <glm/matrix.hpp>

class Object{
    private:
        std::unique_ptr<VAO> vao;
        std::unique_ptr<VBO> vbo;
        std::unique_ptr<ShaderProgram> shader;
        glm::vec3 position;

    public:
        Object(std::string modelPath, std::string shaderPath);
        ~Object();
        void draw();
};


#endif // OBJECT_H_
