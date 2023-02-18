#ifndef VBO_H_
#define VBO_H_

#include "interface.hpp"

class VBO : public Bindable, public Attribute {
  public:
    VBO(void *data, unsigned int v_size, unsigned int size, unsigned int type);
    ~VBO();
    void bind();
    void unbind();

    inline size_t size() {
        return this->v_size;
    }
    inline size_t stride() {
        return this->_stride;
    }
    inline size_t offset() {
        return this->_offset;
    }

    inline unsigned int type() {
        return this->_type;
    }

  private:
    unsigned int id;
    size_t v_size;
    size_t _stride;
    size_t _offset;
    unsigned int _type;
};

#endif // VBO_H_
