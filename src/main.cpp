#include "VAO.hpp"
#include "VBO.hpp"
#include "gl.h"
#include "log.hpp"
#include "shaders.hpp"
#include "texture.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <string>

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

    std::vector<float> rect = {
        //  (x,y,z)   (r,g,b,a)   (Tx,Ty)
        -0.5f, -0.5f, 0.0f, /**/ 1.0f, 0.0f, 0.0f, 1.0f, /**/ 0.0f, 0.0f, //
        0.5f,  -0.5f, 0.0f, /**/ 0.0f, 1.0f, 0.0f, 1.0f, /**/ 1.0f, 0.0f, //
        0.5f,  0.5f,  0.0f, /**/ 0.0f, 0.0f, 1.0f, 1.0f, /**/ 1.0f, 1.0f, //
        -0.5f, 0.5f,  0.0f, /**/ 0.0f, 1.0f, 0.0f, 1.0f, /**/ 0.0f, 1.0f  //
    };

    auto vbo = VBO(rect);

    auto vao = VAO();
    vao.addAttribute(vbo, 0, 3, 9, 0);
    vao.addAttribute(vbo, 1, 4, 9, 3);
    vao.addAttribute(vbo, 2, 2, 9, 7);

    auto texture = Texture("res/face.png");

    std::vector<unsigned int> indices = {0, 1, 2, 0, 2, 3};
    auto idx = vao.addIndexBuffer(indices);
    vao.attachIndexBuffer(idx);
    auto shader = ShaderProgram("basic.glsl");
    float frame = 0.0f;
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        shader.use();
        shader.setUniformF("u_time", frame);
        texture.bind();

        vao.draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
        frame += 0.01f;
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
