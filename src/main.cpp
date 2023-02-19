
#include "log.h"
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

    // rectangle vertices
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // buttom left
        0.5f,  -0.5f, 0.0f, // buttom right
        0.5f,  0.5f,  0.0f, // top right
        -0.5f, 0.5f,  0.0f  // top left
    };

    VBO_id vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    VAO_id vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    unsigned int IB = 0 ;
    glGenBuffers(1, &IB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    const std::string vertex_shader = R"(
        #version 450 core
        layout (location = 0) in vec3 position;
        void main() {
            gl_Position = vec4(position.x, position.y, position.z, 1.0);
        }
    )";

    const std::string fragment_shader = R"(
        #version 450 core
        out vec4 color;
        void main() {
            color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
        }
    )";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    auto vs_source = vertex_shader.c_str();
    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    auto fs_source = fragment_shader.c_str();
    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);

    int shader_prog = glCreateProgram();
    glAttachShader(shader_prog, fs);
    glAttachShader(shader_prog, vs);
    glLinkProgram(shader_prog);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader_prog);
        glBindVertexArray(vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
