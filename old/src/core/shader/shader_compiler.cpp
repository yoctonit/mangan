//
// Created by ivan on 19.4.2020..
//
#include "shader_compiler.h"
#include <vector>
#include <sstream>


namespace mn {

    // define static members
    GLuint shader_compiler::_shader_id = 0;
    std::string shader_compiler::_error_message{};

    /*
     * Compile shader
     * @param [in] shader_source
     * @param [in] shader_type - GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
     * @param [out] - if true - successful compile and error_message is empty string,
     * else failed compile and client can call error_message to get description of error
     */
    bool shader_compiler::compile(const std::string &shader_source, GLenum shader_type) {
        // Create an empty shader handle
        GLuint shader_id = glCreateShader(shader_type);

        // Send the shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        auto *source = (const GLchar *) shader_source.c_str();
        glShaderSource(shader_id, 1, &source, nullptr);

        // Compile shader_compiler
        glCompileShader(shader_id);

        GLint is_compiled = 0;
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &is_compiled);

        if (is_compiled == GL_FALSE) {
            GLint max_length = 0;
            glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &max_length);

            // The max_length includes the NULL character
            std::vector<GLchar> info_log(max_length);
            glGetShaderInfoLog(shader_id, max_length, &max_length, &info_log[0]);

            // We don't need the shader_compiler anymore.
            glDeleteShader(shader_id);

            // Convert the info_log to string
            std::ostringstream error_message;
            for (GLchar c: info_log) {
                error_message << c;
            }

            // Failed compilation, set id to 0, save error message
            _shader_id = 0;
            _error_message = error_message.str();
            return false;
        }

        // Successfully compiled, save id, empty error message
        _shader_id = shader_id;
        _error_message.erase();
        return true;
    }

}
