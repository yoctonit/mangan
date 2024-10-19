#ifndef INCLUDED_MN_VAO_H
#define INCLUDED_MN_VAO_H

#include <glad/glad.h>
#include <iostream>
#include "Shader.h"
#include "VBO.h"

namespace Mn {

    class VAO {
    public:
        VAO() {
            glGenVertexArrays(1, &_id);
            glBindVertexArray(0);
            std::cout << "Created VAO with id " << _id << "\n";
        }

        ~VAO() {
            std::cout << "Deleted VAO with id " << _id << "\n";
            glDeleteVertexArrays(1, &_id);
        }

        void connect(
                const VBO &buffer,
                const ShaderProgram &shader,
                const std::string &attribute,
                GLint size,
                GLsizei stride,
                const void *pointer
        ) const {
            glBindVertexArray(_id);
            buffer.activate();
            GLuint location = shader.location(attribute);
            glEnableVertexAttribArray(location);
            glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(stride * sizeof(GLfloat)),
                                  pointer);
            glBindVertexArray(0);
        }

        void activate() const {
            glBindVertexArray(_id);
        }

        void draw(GLenum mode, GLint first, GLsizei count) const {
            glBindVertexArray(_id);
            glDrawArrays(mode, first, count);
        }

        [[nodiscard]] unsigned int id() const { return _id; };

    private:
        GLuint _id{};
    };

}

#endif //INCLUDED_MN_VAO_H
