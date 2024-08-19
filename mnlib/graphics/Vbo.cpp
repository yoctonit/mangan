#include "Vbo.h"

namespace Mn {

    Vbo Vbo::FromData(const std::vector<float> &data, GLenum type) {
        Vbo buffer;

        glGenBuffers(1, &buffer.m_id);
        glBindBuffer(GL_ARRAY_BUFFER, buffer.m_id);
        glBufferData(
                GL_ARRAY_BUFFER,
                static_cast<GLsizeiptr>(data.size() * sizeof(float)),
                data.data(),
                type
        );

        std::cout << "Created Vbo buffer with id " << buffer.m_id << "\n";
        return buffer;
    }

    unsigned int Vbo::Id() const {
        return m_id;
    }

    void Vbo::Activate() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
    }

    void Vbo::Release() {
        if (m_id == 0) {
            std::cerr << "Error: Trying to release null Vbo\n";
            return;
        }

        std::cout << "Deleted Vbo buffer with id " << m_id << "\n";
        glDeleteBuffers(1, &m_id);
        m_id = 0;
    }

    void Vbo::Debug(const std::string &msg) const {
        std::cout << msg << " has id " << m_id << "\n";
    }

}
