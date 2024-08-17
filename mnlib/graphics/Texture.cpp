#include <iostream>
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb/stb_image.h"

namespace Mn {

    Texture Texture::FromImage(const std::string &fileName) {
        Texture tex;

        // load image
        // prevents inverted images
        stbi_set_flip_vertically_on_load(true);

        int nrChannels;
        unsigned char *data = stbi_load(fileName.c_str(), &tex.m_width, &tex.m_height, &nrChannels, 0);

        int format = GL_RGBA;
        if (nrChannels == 3) {
            format = GL_RGB;
        }

        if (data == nullptr) {
            std::cerr << "Failed to load texture " << fileName << std::endl;
            return tex;
        }

        // create texture object
        glGenTextures(1, &tex.m_id);

        // specify texture used by the following functions
        glBindTexture(GL_TEXTURE_2D, tex.m_id);

        // send pixel data to texture buffer
        glTexImage2D(GL_TEXTURE_2D, 0, format, tex.m_width, tex.m_height, 0, format, GL_UNSIGNED_BYTE, data);

        // generate mipmap image from uploaded pixel data
        glGenerateMipmap(GL_TEXTURE_2D);

        // specify technique for magnifying/minifying textures
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        // specify what happens to texture coordinates outside range [0, 1]
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // set default border color to white; important for rendering shadows
        float borderColor[4]{1.0f, 1.0f, 1.0f, 1.0f};
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(data);

        std::cout << "Created texture " << fileName << " with id " << tex.m_id << "\n";
        return tex;
    }

// generate an empty texture - used by RenderTarget class
//    Texture::Texture(int width, int height, int magFilter, int minFilter, int wrap) {
//        m_width = width;
//        m_height = height;
//
//        // create texture object
//        glGenTextures(1, &m_id);
//
//        // specify texture used by the following functions
//        glBindTexture(GL_TEXTURE_2D, m_id);
//
//        // reserve buffer for pixel data
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
//
//        // generate mipmap image from uploaded pixel data
//        glGenerateMipmap(GL_TEXTURE_2D);
//
//        // specify technique for magnifying/minifying textures
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
//
//        // specify what happens to texture coordinates outside range [0, 1]
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
//
//        // set default border color to white; important for rendering shadows
//        float borderColor[4]{1.0f, 1.0f, 1.0f, 1.0f};
//        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
//
//        glBindTexture(GL_TEXTURE_2D, 0);
//
//        std::cout << "Created empty texture (v1) of size " << m_width << " x " << m_height << "\n";
//    }

//    Texture::Texture(int width, int height) {
//        m_width = width;
//        m_height = height;
//
//        // create texture object
//        glGenTextures(1, &m_id);
//
//        // specify texture used by the following functions
//        glBindTexture(GL_TEXTURE_2D, m_id);
//
//        // reserve buffer for pixel data
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
//
//        // generate mipmap image from uploaded pixel data
//        glGenerateMipmap(GL_TEXTURE_2D);
//
//        // specify technique for magnifying/minifying textures
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//
//        // specify what happens to texture coordinates outside range [0, 1]
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//
//        // set default border color to white; important for rendering shadows
//        float borderColor[4]{1.0f, 1.0f, 1.0f, 1.0f};
//        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
//
//        glBindTexture(GL_TEXTURE_2D, 0);
//
//        std::cout << "Created empty texture of size " << m_width << " x " << m_height << "\n";
//    }

    [[nodiscard]] GLuint Texture::Id() const {
        return m_id;
    }

    [[nodiscard]] int Texture::Width() const {
        return m_width;
    }

    [[nodiscard]] int Texture::Height() const {
        return m_height;
    }

    void Texture::Activate(int textureUnit) const {
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

//        static void Deactivate() {
//            glBindTexture(GL_TEXTURE_2D, 0);
//        }

    void Texture::Release() {
        if (m_id == 0) {
            std::cerr << "Error: Trying to release null texture\n";
            return;
        }
        std::cout << "Deleted texture with id " << m_id << "\n";
        glDeleteTextures(1, &m_id);
        m_id = 0;
    }

    void Texture::Debug(const std::string &msg) const {
        std::cout << msg << "(" << m_width << ", " << m_height << ") has id " << m_id << "\n";
    }

//        [[nodiscard]] std::vector<unsigned char> get_color_array() const {
//            std::vector<unsigned char> pixels(_width *_height*4);
//
//            // create a framebuffer bind it to the texture, and read the color content
//            // Hint from: http://stackoverflow.com/questions/13626606/read-pixels-from-a-webgl-texture
//            unsigned int fb;
//            glGenFramebuffers(1, &fb);
//            glBindFramebuffer(GL_FRAMEBUFFER, fb);
//            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _id, 0);
//            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
//                glReadPixels(0, 0, _width, _height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
//            } else {
//                std::cout << "WARNING: Engine.Textures.get_color_array() failed!\n";
//            }
//            glBindFramebuffer(GL_FRAMEBUFFER, 0);
//            glDeleteFramebuffers(1, &fb);
//
//            return pixels;
//        }
}
