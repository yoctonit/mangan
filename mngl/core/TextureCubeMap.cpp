#include <iostream>
#include <tuple> // for std::ignore
#include "TextureCubeMap.h"

//#define STB_IMAGE_IMPLEMENTATION

#include "stb/stb_image.h"

namespace Mn {

    std::unordered_map<unsigned int, int> TextureCubeMap::mRefCnt{};

    TextureCubeMap::TextureCubeMap() = default;

    // loads a cube map texture from 6 individual texture faces in the order:
    // +X (right), -X (left), +Y (top), -Y (bottom), +Z (front), -Z (back)
    TextureCubeMap::TextureCubeMap(const std::vector<std::string> &faces) {
        // create texture object
        glGenTextures(1, &mId);

        // specify texture used by the following functions
        glBindTexture(GL_TEXTURE_CUBE_MAP, mId);

//        int width, height, nrChannels;
//        for (unsigned int i = 0; i < faces.size(); i++)
//        {
//            unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
//            if (data)
//            {
//                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//                stbi_image_free(data);
//            }
//            else
//            {
//                std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
//                stbi_image_free(data);
//            }
//        }

        // load images
        // prevents inverted images
        stbi_set_flip_vertically_on_load(false);

        for (unsigned int i = 0; i < faces.size(); i++) {
            int nrChannels;
            unsigned char *data = stbi_load(faces[i].c_str(), &mWidth, &mHeight, &nrChannels, 0);

            int format = GL_RGBA;
            if (nrChannels == 3) {
                format = GL_RGB;
            }

            if (data == nullptr) {
                std::cerr << "Failed to load texture " << faces[i].c_str() << std::endl;
                glDeleteTextures(1, &mId);
                mId = 0;
                mWidth = 0;
                mHeight = 0;
                return;
            }

            // send pixel data to texture buffer
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }

        // generate mipmap image from uploaded pixel data: check this
        // glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

        // specify technique for magnifying/minifying textures
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // specify what happens to texture coordinates outside range [0, 1]
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        // set default border color to white; important for rendering shadows
        // float borderColor[4]{1.0f, 1.0f, 1.0f, 1.0f};
        // glTexParameterfv(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BORDER_COLOR, borderColor);

        // glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

        IncRef();
        std::cout << "Created cube map texture with id " << mId << "\n";
    }

    TextureCubeMap::~TextureCubeMap() {
        int refCnt = DecRef();
        if (refCnt == 0) {
            glDeleteTextures(1, &mId);
            std::cout << "Deleted cube map texture with id " << mId << "\n";
        }
    }

    // copy constructor
    TextureCubeMap::TextureCubeMap(const TextureCubeMap &other) {
        mId = other.mId;
        mWidth = other.mWidth;
        mHeight = other.mHeight;
        IncRef();
    }

    // copy assignment operator (by convention, always return *this)
    TextureCubeMap &TextureCubeMap::operator=(const TextureCubeMap &other) {
        // protect against invalid self-assignment
        if (this == &other) {
            std::cout << "TextureCubeMap self assignment detected.\n";
            return *this;
        }
        // already reference counted id
        if (mId == other.mId) {
            std::cout << "TextureCubeMap assignment with same id detected.\n";
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

    [[nodiscard]] GLuint TextureCubeMap::Id() const {
        return mId;
    }

    [[nodiscard]] int TextureCubeMap::Width() const {
        return mWidth;
    }

    [[nodiscard]] int TextureCubeMap::Height() const {
        return mHeight;
    }

    void TextureCubeMap::Activate(int textureUnit) const {
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_CUBE_MAP, mId);
    }

    void TextureCubeMap::SetParameters(int magFilter, int minFilter, int wrap) const {
        glBindTexture(GL_TEXTURE_CUBE_MAP, mId);

        // specify technique for magnifying/minifying textures
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, magFilter);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, minFilter);

        // specify what happens to texture coordinates outside range [0, 1]
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, wrap);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, wrap);

        // glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    void TextureCubeMap::Debug(const std::string &msg) const {
        std::cout << msg << "(" << mWidth << ", " << mHeight << ") has id " << mId << "\n";
    }

    void TextureCubeMap::IncRef() const {
        // objects with mId = 0 are 'empty' (non-initialized) objects,
        // so don't note their existence in mRefCnt map
        if (mId == 0) {
            return;
        }
        mRefCnt[mId]++;
    }

    [[nodiscard]] int TextureCubeMap::DecRef() const {
        if (mId == 0) {
            // should not happen
            std::cerr << "TextureCubeMap: called DecRef with mId = 0\n";
            return -1;
        }
        mRefCnt[mId]--;
        if (mRefCnt[mId] == 0) {
            mRefCnt.erase(mId);
            return 0;
        }
        return mRefCnt[mId];
    }

    void TextureCubeMap::DebugRefCnt() {
        if (mRefCnt.empty()) {
            std::cout << "RefCnt: <empty>\n";
            return;
        }
        std::cout << "RefCnt:\n";
        for (auto &refCnt: mRefCnt) {
            std::cout << "Id " << refCnt.first << " (cnt=" << refCnt.second << ")\n";
        }
    }

}
