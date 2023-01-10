//
// Created by ivan on 3.5.2020..
//

#include <stdexcept>
#include "buffer_library.h"
// #include <iostream>

namespace mn {

    buffer_library& buffer_library::instance() {
        static buffer_library _instance;
        return _instance;
    }

    bool buffer_library::create(
            const std::string& buffer_name,
            const std::vector<GLfloat> & data,
            GLenum type, GLenum usage) {

        auto search = _library.find(buffer_name);
        if (search != _library.end()) {
            return false; // library already has buffer with that name
        }

        // Insert an item into the map.
        auto iter = _library.insert({ buffer_name, gpu_buffer() });

        // iter.first points to map<string, gpu_buffer> element.
        iter.first->second.create(data, type, usage);

        return true;
    }


    bool buffer_library::create(
            const std::string& buffer_name,
            const GLfloat* data,
            GLsizei size,
            GLenum type,
            GLenum usage) {

        auto search = _library.find(buffer_name);
        if (search != _library.end()) {
            return false; // library already has buffer with that name
        }

        // Insert an item into the map.
        auto iter = _library.insert({ buffer_name, gpu_buffer() });

        // iter.first points to map<string, gpu_buffer> element.
        iter.first->second.create(size * sizeof(GLfloat), type, usage);
        iter.first->second.load_data(size, data);

        return true;
    }


    bool buffer_library::has_buffer(const std::string& buffer_name) {
        auto search = _library.find(buffer_name);
        return !(search == _library.end());
    }


    gpu_buffer& buffer_library::get_buffer(const std::string& buffer_name) {
        auto search = _library.find(buffer_name);
        if (search == _library.end()) {
            throw std::invalid_argument( "Buffer does not exists.");
        }

        return search->second;
    }
}
