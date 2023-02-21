#include "texture.hpp"
#include "log.hpp"
#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#undef STB_IMAGE_IMPLEMENTATION

Texture2D::Texture2D(const std::string &filename) {
    int width, height, channels;
    unsigned char *data =
        stbi_load(filename.c_str(), &width, &height, &channels, 0);

    if (!data) {
        ERROR("Failed to load texture: " << filename);
        return;
    }

    unsigned int tid = 0;
    glGenTextures(1, &tid);
    glBindTexture(GL_TEXTURE_2D, tid);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    this->textureID = tid;
}

Texture2D::~Texture2D() {
    glDeleteTextures(1, &this->textureID);
}

void Texture2D::bind() {
    glBindTexture(GL_TEXTURE_2D, this->textureID);
}

void Texture2D::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
