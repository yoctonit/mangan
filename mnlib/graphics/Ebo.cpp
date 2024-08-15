#include "Ebo.h"

namespace Mn {

    Ebo Ebo::FromData(const std::vector<unsigned int> &data, GLenum type) {
        Ebo buffer;

        glGenBuffers(1, &buffer.m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.m_id);
        glBufferData(
                GL_ELEMENT_ARRAY_BUFFER,
                static_cast<GLsizeiptr>(data.size() * sizeof(unsigned int)),
                data.data(),
                type
        );

        std::cout << "Created Ebo buffer with id " << buffer.m_id << "\n";
        return buffer;
    }

    unsigned int Ebo::Id() const {
        return m_id;
    }

    void Ebo::Activate() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    }

    void Ebo::Release() {
        if (m_id == 0) {
            std::cerr << "Error: Trying to release null Ebo\n";
            return;
        }

        std::cout << "Deleted Ebo buffer with id " << m_id << "\n";
        glDeleteBuffers(1, &m_id);
        m_id = 0;
    }

    void Ebo::Debug(const std::string &msg) const {
        std::cout << msg << " has id " << m_id << "\n";
    }

}
