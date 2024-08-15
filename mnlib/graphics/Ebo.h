#ifndef INCLUDED_MN_GRAPHICS_EBO_H
#define INCLUDED_MN_GRAPHICS_EBO_H

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <vector>

namespace Mn {

    class Ebo {
    public:
        static Ebo FromData(const std::vector<unsigned int> &data, GLenum type = GL_STATIC_DRAW);

        [[nodiscard]] unsigned int Id() const;

        void Activate() const;

        void Release();

        void Debug(const std::string &msg) const;

    private:
        unsigned int m_id{};
    };

}

#endif //INCLUDED_MN_GRAPHICS_EBO_H
