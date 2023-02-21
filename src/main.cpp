#include "VAO.hpp"
#include "VBO.hpp"
#include "log.hpp"
#include "shaders.hpp"
#include "texture.hpp"
#include "window.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

int direction = 1;

float camx = 0.0f;
float camy = 0.0f;
float rotation = 0.0f;

void inputCallback(int key, int scancode, int action, int mods) {

    bool act = action == Action(PRESS) || action == Action(REPEAT);
    // wasd
    if (key == Key(W) && act) {
        camy += 10.0f;
    }
    if (key == Key(S) && act) {
        camy -= 10.0f;
    }
    if (key == Key(A) && act) {
        camx -= 10.0f;
    }
    if (key == Key(D) && act) {
        camx += 10.0f;
    }
    if (key == Key(E) && act) {
        rotation += 1.0f;
    }
    if (key == Key(Q) && act) {
        rotation -= 1.0f;
    }
    if (key == Key(ESCAPE) && act) {
        Window::close();
    }
}

int main() {
    Window::init(800, 600, "Hello World", false);
    Window::setInputCallback(inputCallback);

    std::vector<float> rect = {
        //  (x,y,z)   (r,g,b,a)   (Tx,Ty)
        -0.5f, -0.5f, 0.0f, /**/ 1.0f, 0.0f, 0.0f, 1.0f, /**/ 0.0f, 0.0f, //
        0.5f,  -0.5f, 0.0f, /**/ 0.0f, 1.0f, 0.0f, 1.0f, /**/ 1.0f, 0.0f, //
        0.5f,  0.5f,  0.0f, /**/ 0.0f, 0.0f, 1.0f, 1.0f, /**/ 1.0f, 1.0f, //
        -0.5f, 0.5f,  0.0f, /**/ 0.0f, 1.0f, 0.0f, 1.0f, /**/ 0.0f, 1.0f  //
    };

    std::vector<float> rect2 = {
        //  (x,y,z)   (r,g,b,a)   (Tx,Ty)
        0.0f,   0.0f,   0.0f, /**/ 1.0f, 0.0f, 0.0f, 1.0f, /**/ 1.0f, 1.0f, //
        200.0f, 0.0f,   0.0f, /**/ 0.0f, 1.0f, 0.0f, 1.0f, /**/ 0.0f, 1.0f, //
        200.0f, 200.0f, 0.0f, /**/ 0.0f, 0.0f, 1.0f, 1.0f, /**/ 0.0f, 0.0f, //
        0.0f,   200.0f, 0.0f, /**/ 0.0f, 1.0f, 0.0f, 1.0f, /**/ 1.0f, 0.0f  //
    };

    auto vbo = VBO(rect2);

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
    auto projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f,
                                 static_cast<float>(height), -1.0f, 1.0f);

    // Render loop
    float frame = 0.0f;
    Window::update();
    while (!Window::shouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT);
        shader.use();

        auto model = glm::mat4(1.0f);

        model = glm::translate(model, glm::vec3(camx, camy, 0.0f));
        model = glm::rotate(model, glm::radians(rotation),
                                 glm::vec3(0.0f, 0.0f, 1.0f));

        auto view = glm::mat4(1.0f);

        shader.setUniformM4F("u_model", model);
        shader.setUniformM4F("u_view", view);

        shader.setUniformM4F("u_projection", projection);
        shader.setUniformF("u_time", frame);
        texture.bind();
        vao.draw();
        Window::update();
        frame += direction * 0.1f;
    }

    Window::destroy();
    return 0;
}
