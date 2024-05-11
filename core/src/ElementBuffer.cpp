#include "core/ElementBuffer.h"

#include <glad/glad.h>
#include <vector>
#include <iostream>

namespace Mn {
    ElementBuffer::ElementBuffer() = default;

//    ElementBuffer::ElementBuffer(GLsizeiptr size, GLenum type) {
//        size_ = size;
//        glGenBuffers(1, &id_);
//        glBindBuffer(GL_ARRAY_BUFFER, id_);
//        glBufferData(GL_ARRAY_BUFFER, size, nullptr, type);
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//        std::cout << "Created empty GPU buffer with id " << id_ << " of size " << size << "\n";
//    }
//
//    ElementBuffer::ElementBuffer(const std::vector<float> &data, GLenum type) {
//        size_ = static_cast<GLsizeiptr>(data.size() * sizeof(float));
//        glGenBuffers(1, &id_);
//        glBindBuffer(GL_ARRAY_BUFFER, id_);
//        glBufferData(GL_ARRAY_BUFFER, size_, data.data(), type);
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//        std::cout << "Created GPU buffer with id " << id_ << "\n";
//    }

    void ElementBuffer::Create(GLsizeiptr size, GLenum type) {
        size_ = size;
        glGenBuffers(1, &id_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, type);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        std::cout << "Created empty GPU buffer with id " << id_ << " of size " << size << "\n";
    }

    void ElementBuffer::Create(const std::vector<unsigned int> &data, GLenum type) {
        size_ = static_cast<GLsizeiptr>(data.size() * sizeof(float));
        glGenBuffers(1, &id_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_, data.data(), type);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        std::cout << "Created GPU element buffer with id " << id_ << "\n";
    }

    GLuint ElementBuffer::Id() const {
        return id_;
    };

    void ElementBuffer::Activate() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
    }

    void ElementBuffer::Release() {
        std::cout << "Deleted GPU element buffer with id " << id_ << "\n";
        glDeleteBuffers(1, &id_);
        id_ = 0;
    }

    void ElementBuffer::Load(const std::vector<unsigned int> &data) const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(data.size() * sizeof(unsigned int)),
                        data.data());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

}
