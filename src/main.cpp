#include "log.hpp"
#include "shaders.hpp"
#include "texture.hpp"
#include "window.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/matrix.hpp>
#include "mesh.hpp"

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
    if (key == Key(ESCAPE) && act) {
        Window::close();
    }
}

int main() {

    Window::init(1000, 800, "Hello World", false);
    Window::setInputCallback(inputCallback);
    {
        auto object = Mesh("res/monkey.obj");
        auto shader = ShaderProgram("light.glsl");

        int width, height;
        glm::mat4 projection;

        glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
        glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

        // shader = Shader("light.glsl", {"position", "normal", "texcoord"});
        // Uniform::setmat4();


        glm::vec3 cameraPos(0.0f, 0.0f, -5.0f);

        float frame = 0.0f;
        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        while (!Window::shouldClose()) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            Window::getSize(width, height);
            projection =
                glm::perspective(glm::radians(45.0f),
                                 (float)width / (float)height, 0.01f, 2000.0f);

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(frame),
                                glm::vec3(0.0f, 1.0f, 0.0f));

            glm::mat4 view = glm::mat4(1.0f);

            shader.use();
            cameraPos.x = camx;
            cameraPos.z = camy;
            view = glm::translate(view, cameraPos);

            shader.setUniformM4F("u_model", model);
            shader.setUniformM4F("u_view", view);

            shader.setUniformM4F("u_projection", projection);
            shader.setUniform3F("u_lightPos", lightPos);
            shader.setUniform3F("u_lightColor", lightColor);
            shader.setUniform3F("u_viewPos", cameraPos);

            object.draw();
            Window::update();
            frame += direction * 1.0f;
        }
    }
    Window::destroy();
    return 0;
}
