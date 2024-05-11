#include "core/Buffer.h"

#include <glad/glad.h>
#include <vector>
#include <iostream>

namespace Mn {
    Buffer::Buffer() = default;

    Buffer::Buffer(GLsizeiptr size, GLenum type) {
        size_ = size;
        glGenBuffers(1, &id_);
        glBindBuffer(GL_ARRAY_BUFFER, id_);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, type);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        std::cout << "Created empty GPU buffer with id " << id_ << " of size " << size << "\n";
    }

    Buffer::Buffer(const std::vector<float> &data, GLenum type) {
        size_ = static_cast<GLsizeiptr>(data.size() * sizeof(float));
        glGenBuffers(1, &id_);
        glBindBuffer(GL_ARRAY_BUFFER, id_);
        glBufferData(GL_ARRAY_BUFFER, size_, data.data(), type);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        std::cout << "Created GPU buffer with id " << id_ << "\n";
    }

    void Buffer::Create(GLsizeiptr size, GLenum type) {
        size_ = size;
        glGenBuffers(1, &id_);
        glBindBuffer(GL_ARRAY_BUFFER, id_);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, type);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        std::cout << "Created empty GPU buffer with id " << id_ << " of size " << size << "\n";
    }

    void Buffer::Create(const std::vector<float> &data, GLenum type) {
        size_ = static_cast<GLsizeiptr>(data.size() * sizeof(float));
        glGenBuffers(1, &id_);
        glBindBuffer(GL_ARRAY_BUFFER, id_);
        glBufferData(GL_ARRAY_BUFFER, size_, data.data(), type);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        std::cout << "Created GPU buffer with id " << id_ << "\n";
    }

    GLuint Buffer::Id() const {
        return id_;
    };

    void Buffer::Activate() const {
        glBindBuffer(GL_ARRAY_BUFFER, id_);
    }

    void Buffer::Release() {
        std::cout << "Deleted GPU buffer with id " << id_ << "\n";
        glDeleteBuffers(1, &id_);
        id_ = 0;
    }

    void Buffer::Load(const std::vector<float> &data) const {
        glBindBuffer(GL_ARRAY_BUFFER, id_);
        glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(data.size() * sizeof(float)), data.data());
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

}
