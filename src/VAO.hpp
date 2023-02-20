#ifndef VAO_H_
#define VAO_H_

#include "VBO.hpp"
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
    void draw();
    void addAttribute(VBO &attr, unsigned int index, unsigned int v_size,
                      unsigned int stride, unsigned int offset);
    unsigned int addIndexBuffer(std::vector<unsigned int> &ib);
    void attachIndexBuffer(unsigned int index);

  private:
    unsigned int id;
    int indexBufferIndex = -1;
    std::vector<unsigned int> bufferIndexIDs;
    std::vector<unsigned int> bufferIndexSizes;
};

#endif // VAO_H_
