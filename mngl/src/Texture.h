//
// Created by ivan on 14.1.2023..
//

#ifndef INCLUDED_MN_TEXTURE_H
#define INCLUDED_MN_TEXTURE_H

#include <string>
#include <iostream>
#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

namespace Mn {
    class Texture {
    public:
        // parametrize GL_RGB?
        explicit Texture(const std::string &fileName, GLint format = GL_RGB) {
            glGenTextures(1, &textureRef);
            glBindTexture(GL_TEXTURE_2D, textureRef);

            // set the texture wrapping/filtering options (on currently bound texture)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            // load and generate the texture
            int nrChannels;
            stbi_set_flip_vertically_on_load(true);
            unsigned char *data = stbi_load(fileName.c_str(), &mWidth, &mHeight, &nrChannels, 0);
            if (data) {
                glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, data);
                // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr); empty texture
                glGenerateMipmap(GL_TEXTURE_2D);
                // glBindTexture(GL_TEXTURE_2D, 0);
            } else {
                std::cout << "Failed to load texture" << std::endl;
            }
            stbi_image_free(data);
        }

        void activate() const {
            // Binds texture reference to the current webGL texture functionality
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textureRef);

//            // To prevent texture wrapping
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//
//            // Handles how magnification and minimization filters will work.
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//            // For the texture to look "sharp" do the following:
//            // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
//            // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        }


//        void deactivate() {
//            glBindTexture(GL_TEXTURE_2D, 0);
//        }
        [[nodiscard]] int width() const { return mWidth; }

        [[nodiscard]] int height() const { return mHeight; }

        [[nodiscard]] std::vector<unsigned char> getColorArray() const {
            std::vector<unsigned char> pixels(mWidth * mHeight * 4);

            // create a framebuffer bind it to the texture, and read the color content
            // Hint from: http://stackoverflow.com/questions/13626606/read-pixels-from-a-webgl-texture
            unsigned int fb;
            glGenFramebuffers(1, &fb);
            glBindFramebuffer(GL_FRAMEBUFFER, fb);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureRef, 0);
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
                glReadPixels(0, 0, mWidth, mHeight, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
            } else {
                std::cout << "WARNING: Engine.Textures.getColorArray() failed!\n";
            }
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glDeleteFramebuffers(1, &fb);

            return pixels;
        }
//        std::vector<unsigned char> getColorArray(/* textureName */) {
//            if (mColorArray.empty()) {
//                // create a framebuffer bind it to the texture, and read the color content
//                // Hint from: http://stackoverflow.com/questions/13626606/read-pixels-from-a-webgl-texture
//                unsigned int fb;
//                glGenFramebuffers(1, &fb);
//                glBindFramebuffer(GL_FRAMEBUFFER, fb);
//                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureRef, 0);
//                if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
//                    std::vector<unsigned char> pixels(mWidth * mHeight * 4);
//                    glReadPixels(0, 0, mWidth, mHeight, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
//                    mColorArray = pixels;
//                } else {
//                    std::cout << "WARNING: Engine.Textures.getColorArray() failed!\n";
//                    // throw new Error("WARNING: Engine.Textures.getColorArray() failed!");
//                    // return null;
//                }
//                glBindFramebuffer(GL_FRAMEBUFFER, 0);
//                glDeleteFramebuffers(1, &fb);
//            }
//
//            return mColorArray;
//        }

    private:
        GLuint textureRef{};
        int mWidth{};
        int mHeight{};
//        std::vector<unsigned char> mColorArray;
    };
}

#endif //INCLUDED_MN_TEXTURE_H
