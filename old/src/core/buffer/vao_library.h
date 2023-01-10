//
// Created by ivan on 15.5.2020..
//

#ifndef INCLUDED_VAO_LIBRARY_H
#define INCLUDED_VAO_LIBRARY_H

#include <glad/glad.h>
#include <string>
#include <unordered_map>
#include <functional>

namespace mn {

    class vao_library {
    public:
        static vao_library& instance();

        GLuint create(const std::string& vao_name, const std::function<void()>& bindings);
        GLuint create(const std::string& vao_name);

        bool has_vertex_array_object(const std::string& vao_name);
        GLuint get_vertex_array_object(const std::string& vao_name);

    private:
        vao_library() = default;
        ~vao_library() = default;
        vao_library(const vao_library&) = default;
        const vao_library& operator=(const vao_library& lib) const {
            if (this == &lib) return *this; // self-assignment check
            return *this; // return *this anyway, because it's a singleton
        }

        std::unordered_map<std::string, GLuint> _library;
    };

}

#endif //INCLUDED_VAO_LIBRARY_H
