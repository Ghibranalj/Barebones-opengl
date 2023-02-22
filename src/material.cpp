#include "material.hpp"
#include "shaders.hpp"
#include <stb_image.h>

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,glm::vec3 emisive,
                   float specularExponent, float transparency,
                   float refractiveIndex, unsigned int illumno,
                   std::string KdPath) {
    this->ambientColor = ambient;
    this->diffuseColor = diffuse;
    this->specularColor = specular;
    this->specularExponent = specularExponent;
    LOG("Specular exponent:" << specularExponent);
    this->transparency = transparency;
    this->refractiveIndex = refractiveIndex;
    this->illumno = illumno;
    this->KdPath = KdPath;
    this->emissive = emisive;

    loadTexture();
}

void Material::loadTexture() {

    int width, height, channels;

    unsigned char *data =
        stbi_load(KdPath.c_str(), &width, &height, &channels, 0);
    if (!data) {
        ERROR("Failed to load texture" << KdPath << " No texture will be used");
        return;
    }

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format = GL_RGB;
    if (channels == 1) {
        format = GL_RED;
    } else if (channels == 3) {
        format = GL_RGB;
    } else if (channels == 4) {
        format = GL_RGBA;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Material::~Material() {
    glDeleteTextures(1, &id);
}
void Material::use(ShaderProgram & shader,unsigned int textureUnit) {
    writeUniforms(shader);
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Material::writeUniforms(ShaderProgram &shader) {

    shader.setUniform("mat_ambient", ambientColor);
    shader.setUniform("mat_diffuse", diffuseColor);
    shader.setUniform("mat_specular", specularColor);

    shader.setUniform("mat_shininess", specularExponent);
    shader.setUniform("mat_transparency", transparency);
    shader.setUniform("mat_refractivity", refractiveIndex);
    shader.setUniform("mat_emissive", emissive);

    shader.setUniform("mat_illumno", illumno);
}
