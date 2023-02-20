#include "VAO.hpp"
#include "VBO.hpp"
#include "log.hpp"
#include "shaders.hpp"
#include "texture.hpp"
#include "window.hpp"

int direction = 1;

void inputCallback(int key , int scancode , int action, int mods){
    if(key == Key(ESCAPE) && action == Action(PRESS)){
        Window::close();
        return;
    }

    if(key == Key(SPACE) && action == Action(PRESS)){
        direction *= -1;
        return;
    }
}

int main() {
    Window::init(640, 480, "Hello World", false);
    Window::setInputCallback(inputCallback);

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

    std::vector<unsigned int> indices = {0, 1, 2, 0, 2, 3};
    auto idx = vao.addIndexBuffer(indices);
    vao.attachIndexBuffer(idx);
    auto shader = ShaderProgram("basic.glsl");

    // Render loop
    float frame = 0.0f;
    Window::update();
    while (!Window::shouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT);
        shader.use();
        shader.setUniformF("u_time", frame);
        texture.bind();

        vao.draw();
        Window::update();
        frame += direction * 0.1f;
    }

    Window::destroy();
    return 0;
}
