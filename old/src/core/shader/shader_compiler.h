//
// Created by ivan on 19.4.2020..
//
#ifndef INCLUDED_SHADER_H
#define INCLUDED_SHADER_H

#include <glad/glad.h>
#include <string>

namespace mn {

    class shader_compiler {

    public:
        static bool compile(const std::string &shader_source, GLenum shader_type);

        [[nodiscard]] static GLuint get_shader_id() { return _shader_id; }
        [[nodiscard]] static std::string get_error_message() { return _error_message; }

    private:
        static GLuint _shader_id;
        static std::string _error_message;
    };

}

#endif // INCLUDED_SHADER_H
