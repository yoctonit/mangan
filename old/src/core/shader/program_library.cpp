//
// Created by ivan on 22.4.2020..
//

#include "program_library.h"
#include "../util/text_file_loader.h"
#include "shader_compiler.h"
#include "program_linker.h"
#include "program_parser.h"
#include <iostream>

namespace mn {

    std::string program_library::base_program_path{"shader/"};

    program_library& program_library::instance() {
        static program_library _instance;
        return _instance;
    }

    shader_program& program_library::get_program(
            const std::string& vertex_shader_file_name,
            const std::string& fragment_shader_file_name
    ) {
        std::string key = vertex_shader_file_name + "_" + fragment_shader_file_name;

        auto search = _library.find(key);
        if (search != _library.end()) {
            return search->second;
        }

        GLuint vertex_shader_id = _compile_shader(vertex_shader_file_name, GL_VERTEX_SHADER);
        GLuint fragment_shader_id = _compile_shader(fragment_shader_file_name, GL_FRAGMENT_SHADER);

        GLuint shader_program_id = _link_shaders(vertex_shader_id, fragment_shader_id);

        auto iter = _library.insert({key, shader_program(shader_program_id)});
        // iter.first points to {key, shader_program}
        // iter.first->second points to shader_program
        shader_program& program = iter.first->second;

        program_parser::parse(program);

        return program;
    }

    shader_program* program_library::get_program_pointer(
            const std::string &vertex_shader_file_name,
            const std::string &fragment_shader_file_name
    ) {
        std::string key = vertex_shader_file_name + "_" + fragment_shader_file_name;

        auto search = _library.find(key);
        if (search != _library.end()) {
            return &search->second;
        }

        GLuint vertex_shader_id = _compile_shader(vertex_shader_file_name, GL_VERTEX_SHADER);
        GLuint fragment_shader_id = _compile_shader(fragment_shader_file_name, GL_FRAGMENT_SHADER);

        GLuint shader_program_id = _link_shaders(vertex_shader_id, fragment_shader_id);

        auto iter = _library.insert({key, shader_program(shader_program_id)});
        // iter.first points to {key, shader_program}
        // iter.first->second points to shader_program
        shader_program& program = iter.first->second;

        program_parser::parse(program);

        // return &iter.first->second;
        return &program;
    }

    GLuint program_library::_compile_shader(const std::string &shader_file_name, GLenum shader_type) {
        // compile vertex shader
        if (!mn::text_file_loader::load(base_program_path + shader_file_name)) {
            std::cout << "can't load shader: " << shader_file_name << "\n";
            return 0;
        }
        if (!mn::shader_compiler::compile(mn::text_file_loader::get_contents(), shader_type)) {
            std::cout << "can't compile shader:\n"
                      << mn::shader_compiler::get_error_message() << "\n";
            return 0;
        }
        return mn::shader_compiler::get_shader_id();
    }

    GLuint program_library::_link_shaders(GLuint vertex_shader_id, GLuint fragment_shader_id) {
        if (!mn::program_linker::link(vertex_shader_id, fragment_shader_id)) {
            std::cout << "can't link shader program: \n"
                      << mn::program_linker::get_error_message() << "\n";
            return 0;
        }
        return mn::program_linker::get_program_id();
    }
}
