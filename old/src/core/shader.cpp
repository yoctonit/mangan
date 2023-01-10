//
// Created by ivan on 24.12.2022..
//
#include "shader.h"
#include "util.h"
#include <vector>
#include <iostream>
#include <sstream>

namespace Mn::Shader {
    GLuint CreateFromFiles(
            const std::string &vertex_shader_file_name,
            const std::string &fragment_shader_file_name
    ) {
        std::string vertex_shader_source = Mn::Util::Load(vertex_shader_file_name);
        GLuint vertex_shader_id = Compile(vertex_shader_source, GL_VERTEX_SHADER);
        std::string fragment_shader_source = Mn::Util::Load(fragment_shader_file_name);
        GLuint fragment_shader_id = Compile(fragment_shader_source, GL_FRAGMENT_SHADER);

        return Link(vertex_shader_id, fragment_shader_id);
    }

    GLint Location(GLuint shader, const std::string &name) {
        GLint location = glGetAttribLocation(shader, name.c_str());
//        if (location == -1) {
//            location = glGetUniformLocation(shader, name.c_str());
//        }
        return location;
    }

    /*
     * Compile shader
     * @param [in] shader_source
     * @param [in] shader_type - GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
     * @param [out] - if true - successful compile and error_message is empty string,
     * else failed compile and client can call error_message to get description of error
     */
    GLuint Compile(const std::string &shader_source, GLenum shader_type) {
        // Create an empty shader handle
        GLuint shader_id = glCreateShader(shader_type);

        // Send the shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        auto *source = (const GLchar *) shader_source.c_str();
        glShaderSource(shader_id, 1, &source, nullptr);
        glCompileShader(shader_id);

        GLint is_compiled = 0;
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &is_compiled);
        if (is_compiled == GL_FALSE) {
            GLint max_length = 0;
            glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &max_length);

            // The max_length includes the NULL character
            std::vector<GLchar> info_log(max_length);
            glGetShaderInfoLog(shader_id, max_length, &max_length, &info_log[0]);

            // We don't need the shader_id anymore.
            glDeleteShader(shader_id);
            shader_id = 0;

            // Convert the info_log to string
            std::ostringstream error_message;
            for (GLchar c: info_log) {
                error_message << c;
            }
//            error_message = error_message.str();
            std::cout << "Compile: " << error_message.str() << "\n";
        }
        return shader_id;
    }

    /*
     * Link shader program
     * @param [in] vertex_shader_id
     * @param [in] fragment_shader_id
     * @param [out] - if true - successful link, else failed link
     * and client can call error_message to get description of error
     */
    GLuint Link(GLuint vertex_shader_id, GLuint fragment_shader_id) {
        // Vertex and fragment shaders are successfully compiled.
        // Now time to link them together into a shader program.
        GLuint program_id = glCreateProgram();
        glAttachShader(program_id, vertex_shader_id);
        glAttachShader(program_id, fragment_shader_id);
        glLinkProgram(program_id);

        GLint is_linked = 0;
        glGetProgramiv(program_id, GL_LINK_STATUS, (int *) &is_linked);
        if (is_linked == GL_FALSE) {
            GLint info_log_length = 0;
            glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);

            // The info_log_length includes the NULL character
            std::vector<GLchar> info_log(info_log_length);
            glGetProgramInfoLog(program_id, info_log_length, &info_log_length, &info_log[0]);

            // We don't need the program anymore.
            glDeleteProgram(program_id);
            program_id = 0;
            // Don't leak shaders either.
            glDeleteShader(vertex_shader_id);
            glDeleteShader(fragment_shader_id);

            // Convert the info_log to string
            std::ostringstream error_message;
            for (GLchar c: info_log) {
                error_message << c;
            }
//            _error_message = error_message.str();
            std::cout << "Link: " << error_message.str() << "\n";
            return program_id;
        }

        // Always detach shaders after a successful link.
        glDetachShader(program_id, vertex_shader_id);
        glDetachShader(program_id, fragment_shader_id);

        return program_id;
    }
}
