#include <glad/glad.h>
#include "Vao.h"

namespace Mn {

    void Vao::Create() {
        glGenVertexArrays(1, &m_id);
        glBindVertexArray(m_id);
        std::cout << "Created VAO with id " << m_id << "\n";
    }

    unsigned int Vao::Id() const {
        return m_id;
    }

    void Vao::Activate() const {
        glBindVertexArray(m_id);
    }

    void Vao::Release() {
        if (m_id == 0) {
            std::cerr << "Error: Trying to release null Vao\n";
            return;
        }

        std::cout << "Deleted VAO with id " << m_id << "\n";
        glDeleteVertexArrays(1, &m_id);
        m_id = 0;
    }

    void Vao::Debug(const std::string &msg) const {
        std::cout << msg << " has id " << m_id << "\n";
    }

    void Vao::Connect(unsigned int index, int size, int stride, const void *pointer) const {
        // (void *) 0
        glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * static_cast<int>(sizeof(float)), pointer);
        glEnableVertexAttribArray(index);
    }

    void Vao::Draw(GLenum mode, int first, int count) const {
        glBindVertexArray(m_id);
        glDrawArrays(mode, first, count);
    }

    void Vao::Draw(GLenum mode, int count, GLenum type, const void *indices) const {
        glBindVertexArray(m_id);
        glDrawElements(mode, count, type, indices);
    }

}
