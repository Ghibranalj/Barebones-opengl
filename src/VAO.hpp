#ifndef VAO_H_
#define VAO_H_

#include "interface.hpp"
#include <GL/glew.h>
#include <stddef.h>

class VAO : public Bindable {
  public:
    // methods
    VAO();
    ~VAO();
    void bind();
    void unbind();
    void addAttribute(Bindable &buf, Attribute &attr, unsigned int index);

  private:
    unsigned int id;
};

#endif // VAO_H_
