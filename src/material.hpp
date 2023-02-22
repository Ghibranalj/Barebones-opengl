#ifndef MATERIAL_H_
#define MATERIAL_H_
#include "glm/glm.hpp"
#include "shaders.hpp"
#include "texture.hpp"
class Material {
  public:
    Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 emissive,
             float specularExponent, float transparency, float refractiveIndex,
             unsigned int illumno, std::string KdPath); // std::string KaPath);
    ~Material();
    void writeUniforms(ShaderProgram &shader);
    void use(ShaderProgram &shader, unsigned int textureUnit);

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
    std::string KdPath;

    // texture data
    unsigned int id;
    char *TextureData;
    void loadTexture();
};
// note: multiple textures per material
// - Ka - (1-texture alpha) * material ambient + texture alpha * texture value
// - Kd - (1-texture alpha) * material diffuse + texture alpha * texture value

// 0		Color on and Ambient off
// 1		Color on and Ambient on
// 2		Highlight on

#endif // MATERIAL_H_
