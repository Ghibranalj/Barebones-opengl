#ifndef BINDABLE_H_
#define BINDABLE_H_
#include <stddef.h>

class Attribute {
  public:
    virtual size_t size() = 0;
    virtual size_t stride() = 0;
    virtual size_t offset() = 0;
    virtual unsigned int type() = 0;
    virtual void bind() = 0;
    virtual void unbind() = 0;
};

#endif // BINDABLE_H_
