#ifndef INCLUDED_MN_TEXTURE_H
#define INCLUDED_MN_TEXTURE_H

#include <string>
#include <iostream>
//#include <vector>
#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

namespace Mn {

    class Texture {
    private:
        GLuint _id{};
        int _width{};
        int _height{};

    public:
        explicit Texture(const std::string &file_name) {
            glGenTextures(1, &_id);
            glBindTexture(GL_TEXTURE_2D, _id);

            // set the texture wrapping/filtering options (on currently bound texture)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            // load and generate the texture
            int nrChannels;
            stbi_set_flip_vertically_on_load(true);
            unsigned char *data = stbi_load(file_name.c_str(), &_width, &_height, &nrChannels, 0);
            GLint format = GL_RGBA;
            if (nrChannels == 3) {
                format = GL_RGB;
            }
            if (data) {
                glTexImage2D(GL_TEXTURE_2D, 0, format, _width, _height, 0, format, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, 0);
                std::cout << "Created texture " << file_name << " with id " << _id << "\n";
            } else {
                std::cout << "Failed to load texture" << file_name << std::endl;
            }
            stbi_image_free(data);
        }

        ~Texture() {
            glDeleteTextures(1, &_id);
            std::cout << "Deleted texture with id " << _id << "\n";
        }

        void activate(int texture_unit = 0) const {
            glActiveTexture(GL_TEXTURE0 + texture_unit);
            glBindTexture(GL_TEXTURE_2D, _id);
        }

        static void deactivate() {
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        [[nodiscard]] int width() const { return _width; }

        [[nodiscard]] int height() const { return _height; }

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
    };

}

#endif //INCLUDED_MN_TEXTURE_H
