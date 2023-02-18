#include "VAO.hpp"
#include "interface.hpp"
#include "log.hpp"

VAO::VAO() {
    glGenVertexArrays(1, &this->id);
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &this->id);
}

void VAO::bind() {
    glBindVertexArray(this->id);
}

void VAO::unbind() {
    glBindVertexArray(0);
}

void VAO::addAttribute(Bindable &buf,Attribute &attr, unsigned int index) {

        auto size = attr.size();
        auto type  = attr.type();
        auto stride = attr.stride();
        auto offset = attr.offset();

        this->bind();
        glEnableVertexAttribArray(index);
        glBindBuffer(GL_ARRAY_BUFFER, 1);
        glVertexAttribPointer(index, size, type, GL_FALSE, stride, NULL);
        buf.unbind();
        this->unbind();
}
