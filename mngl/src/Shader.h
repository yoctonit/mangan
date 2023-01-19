//
// Created by ivan on 9.1.2023..
//

#ifndef INCLUDED_MN_SHADER_H
#define INCLUDED_MN_SHADER_H

#include <glad/glad.h>
#include <string>

namespace Mn::Shader
{
    GLuint CreateFromFiles(const std::string &vertex_shader_file_name, const std::string &fragment_shader_file_name);

//    GLint Location(GLuint shader, const std::string &name);

    GLuint Compile(const std::string &shader_source, GLenum shader_type);

    GLuint Link(GLuint vertex_shader_id, GLuint fragment_shader_id);

}

#endif // INCLUDED_MN_SHADER_H
