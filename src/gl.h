#ifndef GL_H_
#define GL_H_

#include <GL/glew.h>

#ifdef __cplusplus
extern "C" {
#endif
void GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
                            GLenum severity, GLsizei length, const GLchar *msg,
                            const void *data);

#ifdef __cplusplus
}
#endif
#endif // GL_H_
