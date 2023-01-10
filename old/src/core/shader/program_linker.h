//
// Created by ivan on 20.4.2020..
//
#ifndef INCLUDED_PROGRAM_H
#define INCLUDED_PROGRAM_H

#include <glad/glad.h>
#include <string>

namespace mn {

    class program_linker {

    public:
        static bool link(GLuint vertex_shader_id, GLuint fragment_shader_id);

        [[nodiscard]] static GLuint get_program_id() { return _program_id; }
        [[nodiscard]] static std::string get_error_message() { return _error_message; }

    private:
        static GLuint _program_id;
        static std::string _error_message;
    };

}

#endif // INCLUDED_PROGRAM_H
