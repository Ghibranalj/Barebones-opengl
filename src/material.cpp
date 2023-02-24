#include "material.hpp"
#include "shaders.hpp"
#include <stb_image.h>

static bool CreateTexture(std::string path, unsigned int &id) {

    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data =
        stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (!data) {
        ERROR("Failed to load texture" << path << " No texture will be used");
        return false;
    }

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned int format = GL_RGB;
    if (channels == 1)
        format = GL_RED;
    else if (channels == 3)
        format = GL_RGB;
    else if (channels == 4)
        format = GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);
    return true;
}

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
                   glm::vec3 emisive, float specularExponent,
                   float transparency, float refractiveIndex,
                   unsigned int illumno, std::string KdPath,
                   std::string KsPath) {
    this->ambientColor = ambient;
    this->diffuseColor = diffuse;
    this->specularColor = specular;
    this->specularExponent = specularExponent;
    this->transparency = transparency;
    this->refractiveIndex = refractiveIndex;
    this->illumno = illumno;
    this->diffusePath = KdPath;
    this->specularPath = KsPath;
    this->emissive = emisive;

    if (this->ambientColor == glm::vec3(0.0f, 0.0f, 0.0f)) {
        this->ambientColor = glm::vec3(0.2f, 0.2f, 0.2f);
    }
    if (this->diffuseColor == glm::vec3(0.0f, 0.0f, 0.0f)) {
        this->diffuseColor = glm::vec3(0.8f, 0.8f, 0.8f);
    }
    if (this->specularColor == glm::vec3(0.0f, 0.0f, 0.0f)) {
        this->specularColor = glm::vec3(1.0f, 1.0f, 1.0f);
    }

    loadTexture();
}

Material::~Material() {
    if (this->diffuseID != 0)
        glDeleteTextures(1, &diffuseID);
    if (specularID != 0)
        glDeleteTextures(1, &specularID);
}

void Material::loadTexture() {
    if (diffusePath != "")
        CreateTexture(diffusePath, diffuseID);
    if (specularPath != "")
        CreateTexture(specularPath, specularID);
}

void Material::use(ShaderProgram &shader) {
    writeUniforms(shader);
    if (diffuseID != 0) {
        int loc = shader.getUniformLocation("material.diffuseMap");
        if (loc == -1) {
            goto NEXT;
        }
        shader.setUniform(loc, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseID);
        glUniform1i(loc, 0);
    }
NEXT:
    if (specularID != 0) {
        int loc = shader.getUniformLocation("material.specularMap");
        if (loc == -1) {
            return;
        }
        shader.setUniform(loc, 1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularID);
    }
}

void Material::writeUniforms(ShaderProgram &shader) {

    shader.setUniform("material.ambient", ambientColor);
    shader.setUniform("material.diffuse", diffuseColor);
    shader.setUniform("material.specular", specularColor);
    shader.setUniform("material.shininess", specularExponent);
    shader.setUniform("material.transparency", transparency);
    shader.setUniform("material.refractivity", refractiveIndex);
    shader.setUniform("material.emissive", emissive);
    shader.setUniform("material.illumno", illumno);
}
