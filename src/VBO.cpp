
#include <GL/glew.h>
#include "VBO.hpp"

VBO::VBO(void *data, unsigned int v_size ,unsigned int size, unsigned int type) {

    unsigned int id;
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    this->id = id;
    this->v_size = v_size;
    this->_type = type;
    this->_stride = 0;
    this->_offset = 0;
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


