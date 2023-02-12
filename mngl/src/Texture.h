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
            int width, height, nrChannels;
            stbi_set_flip_vertically_on_load(true);
            unsigned char *data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);
            if (data) {
                glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
                // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr); empty texture
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
    private:
        GLuint textureRef{};
    };
}

#endif //INCLUDED_MN_TEXTURE_H
