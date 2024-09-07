//
// Created by ivan on 29.4.2020..
// https://stackoverflow.com/questions/440144/in-opengl-is-there-a-way-to-get-a-list-of-all-uniforms-attribs-used-by-a-shade

#include "program_parser.h"
#include <iostream>

namespace mn {

    void program_parser::parse(shader_program & program) {
        _parse_attributes(program);
        _parse_uniforms(program);
    }

    void program_parser::_parse_attributes(shader_program & program) {
        GLint number_of_attributes;
        glGetProgramInterfaceiv(program._program_id, GL_PROGRAM_INPUT,
                GL_ACTIVE_RESOURCES, &number_of_attributes);

        GLenum properties[] = {GL_NAME_LENGTH, GL_TYPE, GL_LOCATION};

        for(int i = 0; i < number_of_attributes; ++i) {
            GLint results[3];
            glGetProgramResourceiv(program._program_id, GL_PROGRAM_INPUT,
                    i, 3, properties, 3, nullptr, results);

            GLint name_buffer_size = results[0] + 1;
            char * name = new char[name_buffer_size];
            glGetProgramResourceName(program._program_id, GL_PROGRAM_INPUT,
                    i, name_buffer_size, nullptr, name);

            std::string string_name(name);
            program._locations.insert({string_name, results[2]});
            delete [] name;
        }
    }

    void program_parser::_parse_uniforms(shader_program & program) {
        GLint number_of_uniforms;
        glGetProgramInterfaceiv(program._program_id, GL_UNIFORM,
                GL_ACTIVE_RESOURCES, &number_of_uniforms);

        GLenum properties[] = {GL_NAME_LENGTH, GL_TYPE, GL_LOCATION, GL_BLOCK_INDEX};

        for(int i = 0; i < number_of_uniforms; ++i) {
            GLint results[4];
            glGetProgramResourceiv(program._program_id, GL_UNIFORM,
                    i, 4, properties, 4, nullptr, results);

            if (results[3] != -1) continue; // skip uniforms in blocks

            GLint name_buffer_size = results[0] + 1;
            char * name = new char[name_buffer_size];
            glGetProgramResourceName(program._program_id, GL_UNIFORM,
                    i, name_buffer_size, nullptr, name);

            std::string string_name(name);
            program._locations.insert({string_name, results[2]});
            delete [] name;
        }
    }

    void program_parser::print(const shader_program & program) {
        std::cout << "KEY\tELEMENT\n";
        for (auto&& itr : program._locations) {
            std::cout << itr.first << ' ' << itr.second << '\n';
        }
    }

}
