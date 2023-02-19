
#include "VAO.hpp"
#include "VBO.hpp"
#include "gl.hpp"
#include "log.hpp"
#include "shaders.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

typedef unsigned int VBO_id;
typedef unsigned int VAO_id;

int main() {

    if (!glfwInit()) {
        FATAL("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow *window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        FATAL("Failed to create window");
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();
    const GLubyte *renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte *version = glGetString(GL_VERSION);   // version as a string
    LOG("Renderer:" << renderer);
    LOG("OpenGL version supported: " << version);

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(GLDebugMessageCallback, NULL);

    float rect[] = {
        -0.5f, -0.5f, 0.0f, //
        0.5f,  -0.5f, 0.0f, //
        0.5f,  0.5f,  0.0f, //
        -0.5f, 0.5f,  0.0f  //
    };

    auto vbo = VBO(rect, 3, sizeof(rect), GL_FLOAT);
    auto vao = VAO();
    std::vector<unsigned int> indices = {0, 1, 2, 0, 2, 3};

    vao.addAttribute(vbo, 0);
    auto idx = vao.addIndexBuffer(indices);
    vao.attachIndexBuffer(idx);

    auto shader = ShaderProgram("basic.glsl");

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        shader.use();
        vao.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
