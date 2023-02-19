
#include <GL/glew.h>
#include "VBO.hpp"
#include <vector>

VBO::VBO(std::vector<float> &data) {
    unsigned int id;
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    this->id = id;
    this->_type = GL_FLOAT;
}

VBO::~VBO() {
    glDeleteBuffers(1, &this->id);
}

void VBO::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
}

void VBO::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


