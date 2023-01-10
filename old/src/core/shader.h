//
// Created by ivan on 24.12.2022..
//

#ifndef INCLUDED_MN_SHADER_H
#define INCLUDED_MN_SHADER_H

#include <glad/glad.h>
#include <string>

namespace Mn::Shader {
    GLuint CreateFromFiles(const std::string &vertex_shader_file_name, const std::string &fragment_shader_file_name);

    GLint Location(GLuint shader, const std::string &name);

    GLuint Compile(const std::string &shader_source, GLenum shader_type);

    GLuint Link(GLuint vertex_shader_id, GLuint fragment_shader_id);

    class Uniform {
    public:
        Uniform() = default;

        Uniform(GLuint shader, const std::string &name)
                : _location(glGetUniformLocation(shader, name.c_str())) {};

        void uploadMatrix(const float *data) const {
            glUniformMatrix4fv(_location, 1, GL_FALSE, data);
        }

    private:
        GLint _location{};
    };

}

//public static void checkVersion()
//{
//    System.out.println("Vendor: " +
//                       glGetString(GL_VENDOR) );
//    System.out.println("Renderer: " +
//                       glGetString(GL_RENDERER) );
//    System.out.println("OpenGL version supported: " +
//                       glGetString(GL_VERSION) );
//}
#endif //INCLUDED_MN_SHADER_H
