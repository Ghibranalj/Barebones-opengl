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
    if (this->indexBufferIndex < 0) {
        ERROR("VAO::bind() - no index buffer bound");
        return;
    }

    auto idx = this->indexBufferIndex;
    auto ib = this->bufferIndexIDs[idx];
    glBindVertexArray(this->id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
}

void VAO::draw() {
    if (this->indexBufferIndex < 0) {
        ERROR("VAO::draw() - no index buffer bound");
        return;
    }

    this->bind();
    auto idx = this->indexBufferIndex;
    auto count = this->bufferIndexSizes[idx];
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
}

void VAO::unbind() {
    glBindVertexArray(0);
}

void VAO::addAttribute(VBO &attr, unsigned int index, unsigned int v_size,
                       unsigned int stride, unsigned int offset) {

    glBindVertexArray(this->id);
    attr.bind();
    glEnableVertexAttribArray(index);
    glBindBuffer(GL_ARRAY_BUFFER, 1);
    glVertexAttribPointer(index, v_size, GL_FLOAT, GL_FALSE,
                          stride * sizeof(float),
                          (void *)(offset * sizeof(float)));
    attr.unbind();
    glBindVertexArray(0);
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
    this->bufferIndexSizes.push_back(indices.size());

    assert(this->bufferIndexIDs.size() == this->bufferIndexSizes.size());

    return this->bufferIndexIDs.size() - 1;
}

void VAO::attachIndexBuffer(unsigned int index) {
    this->indexBufferIndex = index;
}
