#ifndef INCLUDED_MN_VBO_H
#define INCLUDED_MN_VBO_H

#include <glad/glad.h>
#include <vector>
#include <iostream>

namespace Mn {

    class VBO {
    public:
        explicit VBO(const std::vector<float> &data, GLenum type = GL_STATIC_DRAW) {
            glGenBuffers(1, &_id);
            glBindBuffer(GL_ARRAY_BUFFER, _id);
            glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(data.size() * sizeof(float)), data.data(), type);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            std::cout << "Created GPU buffer with id " << _id << "\n";
        }

        ~VBO() {
            std::cout << "Deleted GPU buffer with id " << _id << "\n";
            glDeleteBuffers(1, &_id);
        }

        void activate() const {
            glBindBuffer(GL_ARRAY_BUFFER, _id);
        }

        void load(const std::vector<float> &data) const {
            glBindBuffer(GL_ARRAY_BUFFER, _id);
            glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(data.size() * sizeof(float)), data.data());
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        [[nodiscard]] unsigned int id() const { return _id; };

    private:
        GLuint _id{};
    };

}

#endif //INCLUDED_MN_VBO_H
