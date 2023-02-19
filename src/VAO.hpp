#ifndef VAO_H_
#define VAO_H_

#include "interface.hpp"
#include <GL/glew.h>
#include <stddef.h>
#include <vector>

class VAO {
  public:
    // methods
    VAO();
    ~VAO();
    void bind();
    void unbind();
    void addAttribute(Attribute &attr, unsigned int index);
    unsigned int addIndexBuffer(std::vector<unsigned int> &ib);
    void attachIndexBuffer(unsigned int index);

  private:
    unsigned int id;
    unsigned int indexBufferId = 0;
    std::vector<unsigned int> bufferIndexIDs;
};

#endif // VAO_H_
