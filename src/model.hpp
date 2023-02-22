#ifndef MODEL_H_
#define MODEL_H_

#include "material.hpp"
#include "mesh.hpp"
#include "shaders.hpp"
#include <vector>
#include <memory>

#define MODEL_PATH "res/model/"
class Model {
  public:
    Model(const std::string &name);
    void draw(ShaderProgram &shader);

  private:
    std::vector<std::shared_ptr<Material>> materials;
    std::unique_ptr<Mesh> mesh;
};

#endif // MODEL_H_
