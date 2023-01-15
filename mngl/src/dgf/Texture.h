//
// Created by ivan on 14.1.2023..
//

#ifndef INCLUDED_MN_TEXTURE_H
#define INCLUDED_MN_TEXTURE_H

#include <string>
#include "glad/glad.h"
#include "stb_image.h"

class Texture {
// reference of available texture from GPU
public:
    GLuint textureRef;
    int magFilter;
    int minFilter;
    int wrap;
    int width, height;
    int nrChannels;
    unsigned char *pixelData = nullptr;

    // load texture from file
    Texture(const std::string &fileName) {
        magFilter = GL_LINEAR;
        minFilter = GL_LINEAR_MIPMAP_LINEAR;
        wrap = GL_REPEAT;

        pixelData = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);
        uploadData();
    }

    // generate an empty texture - used by RenderTarget class
    // RenderTarget will be implemented later
    Texture(int width_, int height_) {
        width = width_;
        height = height_;
        magFilter = GL_LINEAR;
        minFilter = GL_LINEAR;
        wrap = GL_CLAMP_TO_EDGE;
        uploadData();
    }

    // upload pixel data to GPU
    void uploadData() {
        glGenTextures(1, &textureRef);
        // specify texture used by the following functions
        glBindTexture(GL_TEXTURE_2D, textureRef);
        // send pixel data (ByteBuffer) to texture buffer

        if (pixelData != nullptr)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);
            // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        // generate mipmap image from uploaded pixel data
        glGenerateMipmap(GL_TEXTURE_2D);

        // specify technique for magnifying/minifying textures
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);

        // specify what happens to texture coordinates outside range [0, 1]
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);

        // set default border color to white;
        // important for rendering shadows
//        float[] borderColor = new float[] {1,1,1,1};
        float borderColor[]{1.0f, 1.0f, 1.0f, 1.0f};
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    }
};

#endif //INCLUDED_MN_TEXTURE_H
