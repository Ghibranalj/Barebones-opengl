#ifndef VAO_H_
#define VAO_H_

#include "interface.hpp"
#include <GL/glew.h>
#include <stddef.h>
#include <vector>
#include "VBO.hpp"

class VAO {
  public:
    // methods
    VAO();
    ~VAO();
    void bind();
    void unbind();
    void addAttribute(VBO &attr, unsigned int index, unsigned int v_size,
                      unsigned int stride, unsigned int offset);
    unsigned int addIndexBuffer(std::vector<unsigned int> &ib);
    void attachIndexBuffer(unsigned int index);

  private:
    unsigned int id;
    unsigned int indexBufferId = 0;
    std::vector<unsigned int> bufferIndexIDs;
};

#endif // VAO_H_
