#ifndef MESH_H_
#define MESH_H_

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <memory>

struct Vertex {
    // layout (location = 0) in vec3 position;
    glm::vec3 position;
    // layout (location = 1) in vec3 normal;
    glm::vec3 normal;
    // layout (location = 2) in vec2 uv;
    glm::vec2 uv;
    // layout (location = 3) in vec3 color;
    glm::vec3 color;
};

class Mesh {
  public:
    Mesh(std::string objFile);
    Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices);
    ~Mesh();
    void draw();

  private:
    void init(std::vector<Vertex> &vertices,
              std::vector<unsigned int> &indices);
    unsigned int VAO, VBO, EBO;
    std::unique_ptr<std::vector<Vertex>> vertices;
    std::unique_ptr<std::vector<unsigned int>> indices;
};

#endif // MESH_H_
