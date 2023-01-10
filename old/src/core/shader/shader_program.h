//
// Created by ivan on 28.4.2020..
//

#ifndef INCLUDED_SHADER_PROGRAM_H
#define INCLUDED_SHADER_PROGRAM_H

#include "glad/glad.h"
#include <string>
#include <unordered_map>

namespace mn {

    class shader_program {

    public:
        explicit shader_program(GLuint program_id) : _program_id(program_id) {};

        [[nodiscard]] GLuint handle() const { return _program_id; }
        [[nodiscard]] GLuint location(const std::string& name);

        void print() const;
    private:
        GLuint _get_attribute_location(const std::string& name) const;
        GLuint _get_uniform_location(const std::string& name) const;

        GLuint _program_id;
        std::unordered_map<std::string, GLuint> _locations;

        friend class program_parser;
    };

}

#endif //INCLUDED_SHADER_PROGRAM_H
