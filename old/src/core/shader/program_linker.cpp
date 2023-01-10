//
// Created by ivan on 20.4.2020..
//
#include "program_linker.h"
#include <vector>
#include <sstream>

namespace mn {

    // define static members
    GLuint program_linker::_program_id = 0;
    std::string program_linker::_error_message{};

    /*
     * Link shader program
     * @param [in] vertex_shader_id
     * @param [in] fragment_shader_id
     * @param [out] - if true - successful link, else failed link
     * and client can call error_message to get description of error
     */
    bool program_linker::link(GLuint vertex_shader_id, GLuint fragment_shader_id) {
        // Vertex and fragment shaders are successfully compiled.
        // Now time to link them together into a program.
        // Get a program object.
        GLuint program_id = glCreateProgram();

        // Attach our shaders to our program
        glAttachShader(program_id, vertex_shader_id);
        glAttachShader(program_id, fragment_shader_id);

        // Link our program
        glLinkProgram(program_id);

        // Check the program
        GLint is_linked = 0;
        glGetProgramiv(program_id, GL_LINK_STATUS, (int *)&is_linked);

        if (is_linked == GL_FALSE) {
            GLint info_log_length = 0;
            glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
    
            // The info_log_length includes the NULL character
            std::vector<GLchar> info_log(info_log_length);
            glGetProgramInfoLog(program_id, info_log_length, &info_log_length, &info_log[0]);
    
            // We don't need the program anymore.
            glDeleteProgram(program_id);
            // Don't leak shaders either.
            glDeleteShader(vertex_shader_id);
            glDeleteShader(fragment_shader_id);
    
            // Convert the info_log to string
            std::ostringstream error_message;
            for (GLchar c: info_log) {
                error_message << c;
            }

            // Failed linking, set id to 0, save error message
            _program_id = 0;
            _error_message = error_message.str();
            return false;
        }

        // Always detach shaders after a successful link.
        glDetachShader(program_id, vertex_shader_id);
        glDetachShader(program_id, fragment_shader_id);

        // Successfully linked, save id, empty error message
        _program_id = program_id;
        _error_message.erase();
        return true;
    }

}
