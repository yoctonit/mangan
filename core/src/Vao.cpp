#include "core/Vao.h"
#include <iostream>

namespace Mn {

    Vao::Vao() = default;

    void Vao::Create() {
        glGenVertexArrays(1, &id_);
        glBindVertexArray(0);
        std::cout << "Created Vao with id " << id_ << "\n";
    }

    GLuint Vao::Id() const {
        return id_;
    }

    void Vao::Connect(
            Buffer buffer,
            ShaderProgram shader,
            const std::string &attribute,
            GLint size,
            GLsizei stride,
            const void *pointer
    ) const {
        Activate();
        buffer.Activate();
        shader.AttachAttribute(attribute, size, stride, pointer);
        Deactivate();
    }

    void Vao::Activate() const {
        glBindVertexArray(id_);
    }

    void Vao::Deactivate() {
        glBindVertexArray(0);
    }

    void Vao::Draw(GLenum mode, GLint first, GLsizei count) const {
        glBindVertexArray(id_);
        glDrawArrays(mode, first, count);
        glBindVertexArray(0);
    }

    void Vao::Draw(GLenum mode, GLsizei count, GLenum type, const void * indices) const {
        glBindVertexArray(id_);
        glDrawElements(mode, count, type, indices);
        glBindVertexArray(0);
    }

    void Vao::Release() const {
        std::cout << "Deleted Vao with id " << id_ << "\n";
        glDeleteVertexArrays(1, &id_);
    }

}
