#ifndef INCLUDED_MN_GRAPHICS_VBO_H
#define INCLUDED_MN_GRAPHICS_VBO_H

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <vector>

namespace Mn {

    class Vbo {
    public:
        static Vbo FromData(const std::vector<float> &data, GLenum type = GL_STATIC_DRAW);

        [[nodiscard]] unsigned int Id() const;

        void Activate() const;

        void Release();

        void Debug(const std::string &msg) const;

    private:
        unsigned int m_id{};
    };

}

#endif //INCLUDED_MN_GRAPHICS_VBO_H

//        void load(const std::vector<float> &data) const {
//            glBindBuffer(GL_ARRAY_BUFFER, m_id);
//            glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(data.size() * sizeof(float)), data.data());
//            glBindBuffer(GL_ARRAY_BUFFER, 0);
//        }
