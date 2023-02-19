#ifndef VBO_H_
#define VBO_H_

#include "interface.hpp"
#include <vector>
class VBO : public Bindable {
  public:
    VBO(std::vector<float> &data);
    ~VBO();
    void bind();
    void unbind();

  private:
    unsigned int id;
    size_t v_size;
    size_t _stride;
    size_t _offset;
    unsigned int _type;
};

#endif // VBO_H_
