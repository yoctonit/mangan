#include <iostream>
#include <tuple> // for std::ignore
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb/stb_image.h"

namespace Mn {

    std::unordered_map<unsigned int, int> Texture::mRefCnt{};

    Texture::Texture() = default;

    Texture::Texture(const std::string &fileName) {
        // load image
        // prevents inverted images
        stbi_set_flip_vertically_on_load(true);

        int nrChannels;
        unsigned char *data = stbi_load(fileName.c_str(), &mWidth, &mHeight, &nrChannels, 0);

        int format = GL_RGBA;
        if (nrChannels == 3) {
            format = GL_RGB;
        }

        if (data == nullptr) {
            std::cerr << "Failed to load texture " << fileName << std::endl;
            mId = 0;
            mWidth = 0;
            mHeight = 0;
            return;
        }

        // create texture object
        glGenTextures(1, &mId);

        // specify texture used by the following functions
        glBindTexture(GL_TEXTURE_2D, mId);

        // send pixel data to texture buffer
        glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, data);

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

        // glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(data);
        IncRef();
        std::cout << "Created texture " << fileName << " with id " << mId << "\n";
    }

    // generate an empty texture - used by RenderTarget class
//    Texture::Texture(int width, int height, int magFilter, int minFilter, int wrap) {
//        mWidth = width;
//        mHeight = height;
//
//        // create texture object
//        glGenTextures(1, &mId);
//
//        // specify texture used by the following functions
//        glBindTexture(GL_TEXTURE_2D, mId);
//
//        // reserve buffer for pixel data
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
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
//        std::cout << "Created empty texture (v1) of size " << mWidth << " x " << mHeight << "\n";
//    }

//    Texture::Texture(int width, int height) {
//        mWidth = width;
//        mHeight = height;
//
//        // create texture object
//        glGenTextures(1, &mId);
//
//        // specify texture used by the following functions
//        glBindTexture(GL_TEXTURE_2D, mId);
//
//        // reserve buffer for pixel data
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
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
//        std::cout << "Created empty texture of size " << mWidth << " x " << mHeight << "\n";
//    }

    Texture::~Texture() {
        int refCnt = DecRef();
        if (refCnt == 0) {
            glDeleteTextures(1, &mId);
            std::cout << "Deleted texture with id " << mId << "\n";
        }
    }

    // copy constructor
    Texture::Texture(const Texture &other) {
        mId = other.mId;
        mWidth = other.mWidth;
        mHeight = other.mHeight;
        IncRef();
    }

    // copy assignment operator (by convention, always return *this)
    Texture &Texture::operator=(const Texture &other) {
        // protect against invalid self-assignment
        if (this == &other) {
            std::cout << "Texture self assignment detected.\n";
            return *this;
        }
        // already reference counted id
        if (mId == other.mId) {
            std::cout << "Texture assignment with same id detected.\n";
            return *this;
        }
        if (mId != 0) {
            std::ignore = DecRef();
        }
        mId = other.mId;
        mWidth = other.mWidth;
        mHeight = other.mHeight;
        IncRef();
        return *this;
    }

    [[nodiscard]] GLuint Texture::Id() const {
        return mId;
    }

    [[nodiscard]] int Texture::Width() const {
        return mWidth;
    }

    [[nodiscard]] int Texture::Height() const {
        return mHeight;
    }

    void Texture::Activate(int textureUnit) const {
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, mId);
    }

//        static void Deactivate() {
//            glBindTexture(GL_TEXTURE_2D, 0);
//        }

    void Texture::SetParameters(int magFilter, int minFilter, int wrap) const {
        glBindTexture(GL_TEXTURE_2D, mId);

        // specify technique for magnifying/minifying textures
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);

        // specify what happens to texture coordinates outside range [0, 1]
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);

        // glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::Debug(const std::string &msg) const {
        std::cout << msg << "(" << mWidth << ", " << mHeight << ") has id " << mId << "\n";
    }

    void Texture::IncRef() const {
        // objects with mId = 0 are 'empty' (non-initialized) objects,
        // so don't note their existence in mRefCnt map
        if (mId == 0) {
            return;
        }
        mRefCnt[mId]++;
    }

    [[nodiscard]] int Texture::DecRef() const {
        if (mId == 0) {
            // should not happen
            std::cerr << "Texture: called DecRef with mId = 0\n";
            return -1;
        }
        mRefCnt[mId]--;
        if (mRefCnt[mId] == 0) {
            mRefCnt.erase(mId);
            return 0;
        }
        return mRefCnt[mId];
    }

    void Texture::DebugRefCnt() {
        if (mRefCnt.empty()) {
            std::cout << "RefCnt: <empty>\n";
            return;
        }
        std::cout << "RefCnt:\n";
        for (auto &refCnt: mRefCnt) {
            std::cout << "Id " << refCnt.first << " (cnt=" << refCnt.second << ")\n";
        }
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
