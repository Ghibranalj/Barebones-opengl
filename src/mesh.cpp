#include "GL/glew.h"
#include "log.hpp"
#include "mesh.hpp"
#include <vector>
#include <string>
#include <fstream>

static bool LoadOBJ(std::string objFile, std::vector<Vertex> *vert,
                    std::vector<unsigned int> *indices) {

    std::vector<glm::vec3> temp_position;
    std::vector<glm::vec2> temp_uv;
    std::vector<glm::vec3> temp_normal;

    std::ifstream file(objFile);

    if (!file.is_open()) {
        ERROR("Failed to open file");
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::string delim = " ";
        std::string token = line.substr(0, line.find(delim));

        char *cline = new char[line.length() + 1];
        strcpy(cline, line.c_str());

        if (token == "v") {
            glm::vec3 position;
            sscanf(cline, "v %f %f %f", &position.x, &position.y, &position.z);
            temp_position.push_back(position);
            continue;
        }

        if (token == "vt") {
            glm::vec2 uv;
            sscanf(cline, "vt %f %f", &uv.x, &uv.y);
            temp_uv.push_back(uv);
            continue;
        }

        if (token == "vn") {
            glm::vec3 normal;
            sscanf(cline, "vn %f %f %f", &normal.x, &normal.y, &normal.z);
            temp_normal.push_back(normal);
            continue;
        }

        // always at the end
        if (token == "f") {
            size_t size = temp_position.size();
            vert->resize(size);
            unsigned int positionIndex[3], uvIndex[3], normalIndex[3];
            int matches =
                sscanf(cline, "f %d/%d/%d %d/%d/%d %d/%d/%d", &positionIndex[0],
                       &uvIndex[0], &normalIndex[0], &positionIndex[1],
                       &uvIndex[1], &normalIndex[1], &positionIndex[2],
                       &uvIndex[2], &normalIndex[2]);
            if (matches != 9) {
                ERROR("File can't be read by our simple parser : ( Try "
                      "exporting with other options");
                return false;
            }

            for (int i = 0; i < 3; i++) {
                auto index = positionIndex[i] - 1;
                Vertex vertex;
                vertex.position = temp_position[index];
                vertex.uv = temp_uv[uvIndex[i] - 1];
                vertex.normal = temp_normal[normalIndex[i] - 1];
                vert->at(index) = vertex;
                indices->push_back(index);
            }

            continue;
        }
    }

    return true;
}

Mesh::Mesh(std::string objFile) {
    std::vector<Vertex> *vert = new std::vector<Vertex>();
    std::vector<unsigned int> *indices = new std::vector<unsigned int>();
    LoadOBJ(objFile, vert, indices);
    // call the other constructor
    init(*vert, *indices);
    delete vert;
    delete indices;
}

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) {
    init (vertices, indices);
}

void Mesh::init(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices){
    unsigned int vao, vbo, ebo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    if (vao == 0 || vbo == 0 || ebo == 0) {
        FATAL("Failed to create buffers");
    }
    // binding attributes
    size_t stride = sizeof(Vertex);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
                 &vertices[0], GL_STATIC_DRAW);

    glBindVertexArray(vao);
    // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride,
                          (void *)offsetof(Vertex, position));

    // normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride,
                          (void *)offsetof(Vertex, normal));

    // uv
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride,
                          (void *)offsetof(Vertex, uv));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride,
                          (void *)offsetof(Vertex, color));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 &indices[0], GL_STATIC_DRAW);

    VAO = vao;
    VBO = vbo;
    EBO = ebo;
    // copy vertex in the heap
    this->vertices = new std::vector<Vertex>(vertices);
    this->indices = new std::vector<unsigned int>(indices);
}



void Mesh::draw() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices->size(), GL_UNSIGNED_INT, 0);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    delete[] vertices;
    delete[] indices;
}
