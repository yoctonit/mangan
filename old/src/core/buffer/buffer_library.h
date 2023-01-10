//
// Created by ivan on 3.5.2020..
//

#ifndef INCLUDED_BUFFER_LIBRARY_H
#define INCLUDED_BUFFER_LIBRARY_H


#include <glad/glad.h>
#include <string>
#include <vector>
#include <unordered_map>
#include "gpu_buffer.h"

namespace mn {

    class buffer_library {
    public:
        static buffer_library& instance();

        bool create(
                const std::string& buffer_name,
                const std::vector<GLfloat> & data,
                GLenum type,
                GLenum usage = GL_STATIC_DRAW);

        bool create(
                const std::string& buffer_name,
                const GLfloat* data,
                GLsizei size,
                GLenum type,
                GLenum usage = GL_STATIC_DRAW);

        bool has_buffer(const std::string& buffer_name);
        gpu_buffer& get_buffer(const std::string& buffer_name);

    private:
        buffer_library() = default;
        ~buffer_library() = default;
        buffer_library(const buffer_library&) = default;
        const buffer_library& operator=(const buffer_library& lib) const {
            if (this == &lib) return *this; // self-assignment check
            return *this; // return *this anyway, because it's a singleton
        }

        std::unordered_map<std::string, gpu_buffer> _library;
    };

}

#endif //INCLUDED_BUFFER_LIBRARY_H
