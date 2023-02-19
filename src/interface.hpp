#ifndef BINDABLE_H_
#define BINDABLE_H_
#include <stddef.h>

class Bindable {
  public:
    virtual void bind() = 0;
    virtual void unbind() = 0;
};

#endif // BINDABLE_H_
