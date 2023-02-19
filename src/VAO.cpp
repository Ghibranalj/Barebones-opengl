#include "VAO.hpp"
#include "interface.hpp"
#include "log.hpp"
#include <cassert>

VAO::VAO() {
    glGenVertexArrays(1, &this->id);
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &this->id);
}

void VAO::bind() {
    glBindVertexArray(this->id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferId);
}

void VAO::unbind() {
    glBindVertexArray(0);
}

void VAO::addAttribute(Attribute &attr, unsigned int index) {

    auto size = attr.size();
    auto type = attr.type();
    auto stride = attr.stride();
    auto offset = attr.offset();

    this->bind();
    attr.bind();
    glEnableVertexAttribArray(index);
    glBindBuffer(GL_ARRAY_BUFFER, 1);
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, NULL);
    attr.unbind();
    this->unbind();
}

// return index
unsigned int VAO::addIndexBuffer(std::vector<unsigned int> &indices) {
    unsigned int id = 0;
    glGenBuffers(1, &id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 &indices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    this->bufferIndexIDs.push_back(id);
    return this->bufferIndexIDs.size() - 1;
}

void VAO::attachIndexBuffer(unsigned int index) {
    indexBufferId = this->bufferIndexIDs[index];
}
