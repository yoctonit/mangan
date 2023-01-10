//
// Created by ivan on 22.4.2020..
//

#ifndef INCLUDED_PROGRAM_LIBRARY_H
#define INCLUDED_PROGRAM_LIBRARY_H

#include <glad/glad.h>
#include <string>
#include <unordered_map>
#include "shader_program.h"

namespace mn {

    class program_library {

    public:
        static program_library& instance();

        shader_program& get_program(const std::string& vertex_shader_file_name,
                const std::string& fragment_shader_file_name);
        shader_program* get_program_pointer(const std::string& vertex_shader_file_name,
                                    const std::string& fragment_shader_file_name);

    private:
        program_library() = default;
        ~program_library() = default;
        program_library(const program_library&) = default;
        const program_library& operator=(const program_library& lib) const {
            if (this == &lib) return *this; // self-assignment check
            return *this; // return *this anyway, because it's a singleton
        }

        static GLuint _compile_shader(const std::string &shader_file_name, GLenum shader_type);
        static GLuint _link_shaders(GLuint vertex_shader_id, GLuint fragment_shader_id);

        std::unordered_map<std::string, shader_program> _library;

        static std::string base_program_path;
    };

}

#endif //INCLUDED_PROGRAM_LIBRARY_H
