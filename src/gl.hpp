#ifndef GL_H_
#define GL_H_

#include <GL/glew.h>

void GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
                            GLenum severity, GLsizei length,
                            const GLchar *msg, const void *data);

#endif // GL_H_
