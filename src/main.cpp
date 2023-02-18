
#include "log.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <assert.h>
#include <cstdlib>
#include <fcntl.h>
#include <fstream>
#include <string>

#include "VAO.hpp"
#include "VBO.hpp"
#include "shaders.hpp"

int main() {

    LOG("Starting GLFW context, OpenGL 3.3");
    // read /res/test.txt and log it

    std::string path = "res/test.txt";
    std::fstream file;

    file.open(path, std::ios::in);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            LOG(line);
        }
        file.close();
    }

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

    float *vertices = new float[9]{
        -0.5f, -0.5f, 0.0f, // left
        0.5f,  -0.5f, 0.0f, // right
        0.0f,  0.5f,  0.0f  // top
    };

    auto vbo = VBO(vertices, 3, sizeof(float) * 9, GL_FLOAT);
    delete[] vertices;

    auto vao = VAO();
    vao.addAttribute(vbo, 0);

    auto shaderp = ShaderProgram("basic.glsl");

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        shaderp.use();
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
