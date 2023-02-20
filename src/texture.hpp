#ifndef IMAGE_H_
#define IMAGE_H_

#include <string>

class Texture2D {
public:
    Texture2D(const std::string& filename);
    ~Texture2D();
    void bind();
    void unbind();
private:
    int width;
    int height;
    int channels;
    unsigned char* data;
    unsigned int textureID;
};


#endif // IMAGE_H_
