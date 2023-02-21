#include "object.hpp"
#include "shaders.hpp"
#include <cstring>
#include <glm/fwd.hpp>
#include <memory>
#include <string>

static bool LoadOBJ(std::string modelPath, std::vector<float> &vertices,
                    std::vector<unsigned int> &indices,
                    std::string vertexLayout) {

    std::vector<glm::vec3> temp_position;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;


    FILE *file = fopen(modelPath.c_str(), "r");
    if (file == NULL) {
        printf("Impossible to open the file !\n");
        return false;
    }


    while (1) {

        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.

        // else : parse lineHeader

        if (strcmp(lineHeader, "v") == 0) {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f", &vertex.x, &vertex.y, &vertex.z);
        }


        else if (strcmp(lineHeader, "vt") == 0) {
            glm::vec2 uv;
            fscanf(file, "%f %f", &uv.x, &uv.y);
        }


        else if (strcmp(lineHeader, "vn") == 0) {
            glm::vec3 normal;
            fscanf(file, "%f %f %f", &normal.x, &normal.y, &normal.z);
        }


        else if (strcmp(lineHeader, "f") == 0) {
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

            if (matches != 9) {
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                return false;
            }

            for (int i = 0; i < 3; i++) {
                indices.push_back(vertexIndex[i]);
            }
        }

    }
}

Object::Object(std::string modelPath, std::string shaderPath) {

    std::vector<float> vertices = {};
    std::vector<unsigned int> indices = {};

    shader = std::make_unique<ShaderProgram>(shaderPath);
    vbo = std::make_unique<VBO>(vertices);
    vao = std::make_unique<VAO>();
}
