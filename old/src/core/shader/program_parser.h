//
// Created by ivan on 29.4.2020..
//

#ifndef INCLUDED_PROGRAM_PARSER_H
#define INCLUDED_PROGRAM_PARSER_H

#include "shader_program.h"

namespace mn {

    class program_parser {
    public:
        static void parse(shader_program & program);
        static void print(const shader_program & program);
    private:
        static void _parse_attributes(shader_program & program);
        static void _parse_uniforms(shader_program & program);
    };

}

#endif //INCLUDED_PROGRAM_PARSER_H
