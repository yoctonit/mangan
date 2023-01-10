//
// Created by ivan on 15.5.2020..
//

#include "vao_library.h"

namespace mn {

    vao_library& vao_library::instance() {
        static vao_library _instance;
        return _instance;
    }


    GLuint vao_library::create(const std::string& vao_name, const std::function<void()>& bindings) {

        auto search = _library.find(vao_name);
        if (search != _library.end()) {
            // library already has VAO with that name, so just return it
            return search->second;
        }

        // else create new VAO
        GLuint vertex_array_id;
        glGenVertexArrays(1, &vertex_array_id);
        glBindVertexArray(vertex_array_id);

        if (bindings != nullptr) bindings();

        glBindVertexArray(0);

        // Insert an item into the map.
        auto iter = _library.insert({ vao_name, vertex_array_id });

        // iter.first points to map<string, gpu_buffer> element.
        return iter.first->second;
    }

    GLuint vao_library::create(const std::string& vao_name) {
        GLuint vertex_array_id;
        glGenVertexArrays(1, &vertex_array_id);
        glBindVertexArray(vertex_array_id);

        // Insert an item into the map.
        auto iter = _library.insert({ vao_name, vertex_array_id });

        // iter.first points to map<string, GLuint> element.
        // return iter.first->second;
        return vertex_array_id;
    }

    bool vao_library::has_vertex_array_object(const std::string& vao_name) {
        auto search = _library.find(vao_name);
        return !(search == _library.end());
    }

    GLuint vao_library::get_vertex_array_object(const std::string &vao_name) {
        auto search = _library.find(vao_name);
        if (search == _library.end()) {
            throw std::invalid_argument( "VAO does not exists.");
        }

        return search->second;
    }
}
