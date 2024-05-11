#ifndef INCLUDED_MN_CORE_ELEMENT_BUFFER_H
#define INCLUDED_MN_CORE_ELEMENT_BUFFER_H

#include <glad/glad.h>
#include <vector>

namespace Mn {

    class ElementBuffer {
    public:
        ElementBuffer();

//        explicit ElementBuffer(GLsizeiptr size, GLenum type = GL_STATIC_DRAW);
//
//        explicit ElementBuffer(const std::vector<float> &data, GLenum type = GL_STATIC_DRAW);

        void Create(GLsizeiptr size, GLenum type = GL_STATIC_DRAW);

        void Create(const std::vector<unsigned int> &data, GLenum type = GL_STATIC_DRAW);

        [[nodiscard]] GLuint Id() const;

        void Activate() const;

        void Release();

        void Load(const std::vector<unsigned int> &data) const;

    private:
        GLuint id_{};
        GLsizeiptr size_{};
    };

}

#endif //INCLUDED_MN_CORE_ELEMENT_BUFFER_H
