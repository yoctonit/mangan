//
// Created by ivan on 28.4.2020..
//

#include "shader_program.h"
#include <iostream>

namespace mn {

    GLuint shader_program::location(const std::string& name) {
        auto search = _locations.find(name);
        if (search != _locations.end()) {
            return search->second;
        }

        GLint location = _get_attribute_location(name);
        if (location == -1) {
            location = _get_uniform_location(name);
        }
        if(location == -1) return location; // we didn't find it

        // else save to locations cache
        _locations.insert({name, location});
        return location;
    }

    GLuint shader_program::_get_attribute_location(const std::string& name) const {
        return glGetAttribLocation(_program_id, name.c_str());
    }

    GLuint shader_program::_get_uniform_location(const std::string& name) const {
        return glGetUniformLocation(_program_id, name.c_str());
    }

    void shader_program::print() const {
        std::cout << "KEY\tELEMENT\n";
        for (auto&& itr : _locations) {
            std::cout << itr.first << ' ' << itr.second << '\n';
        }
    }

}
