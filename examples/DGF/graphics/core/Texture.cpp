#include <iostream>
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb/stb_image.h"

Texture::Texture(const std::string &fileName) {
    m_magFilter = GL_LINEAR;
    m_minFilter = GL_LINEAR_MIPMAP_LINEAR;
    m_wrap = GL_REPEAT;

    // load image

    // prevents inverted images
    stbi_set_flip_vertically_on_load(true);

    int nrChannels;
    unsigned char *data = stbi_load(fileName.c_str(), &m_width, &m_height, &nrChannels, 0);

    GLint format = GL_RGBA;
    if (nrChannels == 3) {
        format = GL_RGB;
    }

    if (data == nullptr) {
        std::cerr << "Failed to load texture" << fileName << std::endl;
        return;
    }

    // create texture object
    glGenTextures(1, &m_textureRef);

    // specify texture used by the following functions
    glBindTexture(GL_TEXTURE_2D, m_textureRef);

    // send pixel data to texture buffer
    glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);

    // generate mipmap image from uploaded pixel data
    glGenerateMipmap(GL_TEXTURE_2D);

    // specify technique for magnifying/minifying textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_magFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_minFilter);

    // specify what happens to texture coordinates outside range [0, 1]
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrap);

    // set default border color to white; important for rendering shadows
    float borderColor[4]{1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);

    std::cout << "Created texture " << fileName << " with id " << m_textureRef << "\n";
}

// generate an empty texture - used by RenderTarget class
Texture::Texture(int width, int height, int magFilter, int minFilter, int wrap) {
    m_width = width;
    m_height = height;

    m_magFilter = magFilter;
    m_minFilter = minFilter;
    m_wrap = wrap;

    // create texture object
    glGenTextures(1, &m_textureRef);

    // specify texture used by the following functions
    glBindTexture(GL_TEXTURE_2D, m_textureRef);

    // reserve buffer for pixel data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    // generate mipmap image from uploaded pixel data
    glGenerateMipmap(GL_TEXTURE_2D);

    // specify technique for magnifying/minifying textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_magFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_minFilter);

    // specify what happens to texture coordinates outside range [0, 1]
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrap);

    // set default border color to white; important for rendering shadows
    float borderColor[4]{1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glBindTexture(GL_TEXTURE_2D, 0);

    std::cout << "Created empty texture (v1) of size " << m_width << " x " << m_height << "\n";
}

Texture::Texture(int width, int height) {
    m_width = width;
    m_height = height;

    m_magFilter = GL_LINEAR;
    m_minFilter = GL_LINEAR;
    m_wrap = GL_CLAMP_TO_EDGE;

    // create texture object
    glGenTextures(1, &m_textureRef);

    // specify texture used by the following functions
    glBindTexture(GL_TEXTURE_2D, m_textureRef);

    // reserve buffer for pixel data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    // generate mipmap image from uploaded pixel data
    glGenerateMipmap(GL_TEXTURE_2D);

    // specify technique for magnifying/minifying textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_magFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_minFilter);

    // specify what happens to texture coordinates outside range [0, 1]
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrap);

    // set default border color to white; important for rendering shadows
    float borderColor[4]{1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glBindTexture(GL_TEXTURE_2D, 0);

    std::cout << "Created empty texture of size " << m_width << " x " << m_height << "\n";
}

//        ~Texture() {
//            glDeleteTextures(1, &_id);
//            std::cout << "Deleted texture with id " << _id << "\n";
//        }

//        void activate(int texture_unit = 0) const {
//            glActiveTexture(GL_TEXTURE0 + texture_unit);
//            glBindTexture(GL_TEXTURE_2D, _id);
//        }
//
//        static void deactivate() {
//            glBindTexture(GL_TEXTURE_2D, 0);
//        }

[[nodiscard]] GLuint Texture::textureRef() const {
    return m_textureRef;
}

[[nodiscard]] int Texture::width() const {
    return m_width;
}

[[nodiscard]] int Texture::height() const {
    return m_height;
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
