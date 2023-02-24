#ifndef MATERIAL_H_
#define MATERIAL_H_
#include "glm/glm.hpp"
#include "shaders.hpp"

class Material {
  public:
    Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 emissive,
             float specularExponent, float transparency, float refractiveIndex,
             unsigned int illumno, std::string diffusePath, std::string specularPath);
    ~Material();
    void writeUniforms(ShaderProgram &shader);
    void use(ShaderProgram &shader);

  private:
    glm::vec3 ambientColor;
    glm::vec3 diffuseColor;
    glm::vec3 specularColor;

    // Ns
    float specularExponent;
    // d
    float transparency;
    // Ni
    float refractiveIndex;
    // Ke
    glm::vec3 emissive;
    unsigned int illumno;
    std::string diffusePath, specularPath;

    // texture data
    unsigned int diffuseID , specularID ;
    char *TextureData;
    void loadTexture();
};

#endif // MATERIAL_H_
