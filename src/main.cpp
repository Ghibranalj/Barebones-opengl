#include "VAO.hpp"
#include "VBO.hpp"
#include "log.hpp"
#include "shaders.hpp"
#include "texture.hpp"
#include "window.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/matrix.hpp>

int direction = 1;

float camx = 0.0f;
float camy = 0.0f;
float rotation = 0.0f;

void inputCallback(int key, int scancode, int action, int mods) {

    bool act = action == Action(PRESS) || action == Action(REPEAT);
    float speed = 0.1f;
    // wasd
    if (key == Key(W) && act) {
        camy += speed;
    }
    if (key == Key(S) && act) {
        camy -= speed;
    }
    if (key == Key(A) && act) {
        camx -= speed;
    }
    if (key == Key(D) && act) {
        camx += speed;
    }
    // if (key == Key(E) && act) {
    //     rotation += 1.0f;
    // }
    // if (key == Key(Q) && act) {
    //     rotation -= 1.0f;
    // }
    if (key == Key(ESCAPE) && act) {
        Window::close();
    }
}

int main() {
    Window::init(800, 600, "Hello World", false);
    Window::setInputCallback(inputCallback);

    std::vector<float> rect2 = {
        //  (x,y,z)   (r,g,b,a)   (Tx,Ty)
        0.0f, 0.0f, 0.0f, /**/ 1.0f, 0.0f, 0.0f, 1.0f, /**/ 1.0f, 1.0f, //
        1.0f, 0.0f, 0.0f, /**/ 0.0f, 1.0f, 0.0f, 1.0f, /**/ 0.0f, 1.0f, //
        1.0f, 1.0f, 0.0f, /**/ 0.0f, 0.0f, 1.0f, 1.0f, /**/ 0.0f, 0.0f, //
        0.0f, 1.0f, 0.0f, /**/ 0.0f, 1.0f, 0.0f, 1.0f, /**/ 1.0f, 0.0f  //
    };

    std::vector<float> cube = {
        // (x,y,z)  (r,g,b,a)   (Tx,Ty)
        -1.0f, -1.0f, -1.0f, /**/ 1.0f, 0.0f, 0.0f, 1.0f, /**/ 0.0f, 0.0f, //
        1.0f,  -1.0f, -1.0f, /**/ 0.0f, 1.0f, 0.0f, 1.0f, /**/ 1.0f, 0.0f, //
        1.0f,  1.0f,  -1.0f, /**/ 0.0f, 0.0f, 1.0f, 1.0f, /**/ 1.0f, 1.0f, //
        -1.0f, 1.0f,  -1.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 1.0f, //
        -1.0f, -1.0f, 1.0f,  /**/ 1.0f, 0.0f, 0.0f, 1.0f, /**/ 0.0f, 0.0f, //
        1.0f,  -1.0f, 1.0f,  /**/ 0.0f, 1.0f, 0.0f, 1.0f, /**/ 1.0f, 0.0f, //
        1.0f,  1.0f,  1.0f,  /**/ 0.0f, 0.0f, 1.0f, 1.0f, /**/ 1.0f, 1.0f, //
        -1.0f, 1.0f,  1.0f,  /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 1.0f, //
    };

    std::vector<unsigned int> indices_cube = {
        0, 1, 3, 3, 1, 2, //
        1, 5, 2, 2, 5, 6, //
        5, 4, 6, 6, 4, 7, //
        4, 0, 7, 7, 0, 3, //
        3, 2, 7, 7, 2, 6, //
        4, 5, 0, 0, 5, 1  //
    };

    auto vbo = VBO(cube);

    auto vao = VAO();
    vao.addAttribute(vbo, 0, 3, 9, 0);
    vao.addAttribute(vbo, 1, 4, 9, 3);
    vao.addAttribute(vbo, 2, 2, 9, 7);

    std::vector<unsigned int> indices = {0, 1, 2, 0, 2, 3};
    auto idx = vao.addIndexBuffer(indices);
    vao.attachIndexBuffer(idx);

    auto texture = Texture2D("res/face.png");

    auto shader = ShaderProgram("basic.glsl");

    int width, height;
    Window::getSize(width, height);

    glm::mat4 projection;

    projection = glm::perspective(glm::radians(45.0f),
                                  (float)width / (float)height, 0.01f, 2000.0f);

    float frame = 0.0f;
    glEnable(GL_CULL_FACE);
    Window::update();
    while (!Window::shouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT);

        Window::getSize(width, height);

        projection = glm::perspective(
            glm::radians(45.0f), (float)width / (float)height, 0.01f, 2000.0f);

        shader.use();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(camx, camy, 0.0f));
        model = glm::rotate(model, glm::radians(frame),
                            glm::vec3(0.0f, 1.0f, 1.0f));

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));

        shader.setUniformM4F("u_model", model);
        shader.setUniformM4F("u_view", view);

        shader.setUniformM4F("u_projection", projection);
        shader.setUniformF("u_time", frame);
        texture.bind();
        vao.draw();
        Window::update();
        frame += direction * 1.0f;
    }

    Window::destroy();
    return 0;
}
