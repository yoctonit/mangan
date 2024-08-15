#ifndef INCLUDED_MN_GRAPHICS_VAO_H
#define INCLUDED_MN_GRAPHICS_VAO_H

#include <glad/glad.h>
#include <iostream>
#include <string>


namespace Mn {

    class Vao {
    public:
        void Create();

        [[nodiscard]] unsigned int Id() const;

        void Activate() const;

        void Release();

        void Debug(const std::string &msg) const;

        void Connect(unsigned int index, int size, int stride, const void *pointer) const;

        void Draw(GLenum mode, int first, int count) const;

        void Draw(GLenum mode, int count, GLenum type, const void * indices) const;

    private:
        unsigned int m_id{};
    };

}

#endif //INCLUDED_MN_GRAPHICS_VAO_H
