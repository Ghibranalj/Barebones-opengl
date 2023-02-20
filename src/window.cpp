#include <GL/glew.h>
#include "window.hpp"
#include "gl.h"
#include "log.hpp"
#include <GLFW/glfw3.h>

namespace Window {

struct window_t {
    GLFWwindow *window;
    inputCallback callback;
};

window_t window_i;

void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                 int mods);

void init(unsigned int width, unsigned int height, std::string title,
          bool resizable) {

    if (!glfwInit()) {
        FATAL("Failed to initialize GLFW");
    }

    if (resizable) {
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    } else {
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    }

    window_i.window =
        glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window_i.window) {
        FATAL("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window_i.window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        FATAL("Failed to initialize GLEW");
    }

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(GLDebugMessageCallback, NULL);

    glfwSetKeyCallback(window_i.window, keyCallback);
    window_i.callback = NULL;
}

int shouldClose() {
    return glfwWindowShouldClose(window_i.window);
}

void update() {
    glfwSwapBuffers(window_i.window);
    glfwPollEvents();
}

void destroy() {
    glfwDestroyWindow(window_i.window);
    glfwTerminate();
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                 int mods) {
    if (window_i.callback == NULL)
        return;

    window_i.callback(key, scancode, action, mods);
}

void setInputCallback(inputCallback callback) {
    window_i.callback = callback;
}

void close() {
    glfwSetWindowShouldClose(window_i.window, GL_TRUE);
}

void toggleVsync(bool enable) {
    glfwSwapInterval((enable) ? 1 : 0);
}

} // namespace Window
