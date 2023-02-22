#include "texture.hpp"
#include "log.hpp"
#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#undef STB_IMAGE_IMPLEMENTATION

Texture::Texture(const std::string &filename) {
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

    this->textureID = tid;
}

Texture::~Texture() {
    glDeleteTextures(1, &this->textureID);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, this->textureID);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
