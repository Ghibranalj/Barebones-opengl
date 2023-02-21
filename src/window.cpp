#include <GL/glew.h>
#include "window.hpp"
#include "gl.h"
#include "log.hpp"
#include <GLFW/glfw3.h>

struct window {
    GLFWwindow *window;
    Window::inputCallback callback;
    bool vSyncEnabled;
};

static window window{nullptr, nullptr, false};

static void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                 int mods);

void Window::init(unsigned int width, unsigned int height, std::string title,
                  bool resizable) {

    if (!glfwInit()) {
        FATAL("Failed to initialize GLFW");
    }

    if (resizable) {
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    } else {
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    }


    window.window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window.window) {
        FATAL("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window.window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        FATAL("Failed to initialize GLEW");
    }

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(GLDebugMessageCallback, NULL);

    glfwSetKeyCallback(window.window, keyCallback);
    window.callback = NULL;
}

int Window::shouldClose() {
    return glfwWindowShouldClose(window.window);
}

void Window::update() {
    glfwSwapBuffers(window.window);
    glfwPollEvents();
}

void Window::destroy() {
    glfwDestroyWindow(window.window);
    glfwTerminate();
}

void Window::setInputCallback(inputCallback callback) {
    window.callback = callback;
}

void Window::close() {
    glfwSetWindowShouldClose(window.window, GL_TRUE);
}

void Window::toggleVsync() {
    setVsync(!window.vSyncEnabled);
}

void Window::setVsync(bool enabled) {
    window.vSyncEnabled = enabled;
}

bool Window::isVsyncEnabled() {
    return window.vSyncEnabled;
}

void Window::getSize(int &width, int &height){
    glfwGetWindowSize(window.window, &width, &height);
}

static void keyCallback(GLFWwindow *glfw_window, int key, int scancode, int action,
                 int mods) {
    if (window.callback == nullptr || glfw_window != window.window)
        return;

    window.callback(key, scancode, action, mods);
}
