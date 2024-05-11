#ifndef INCLUDED_MN_CORE_VAO_H
#define INCLUDED_MN_CORE_VAO_H

#include "Shader.h"
#include "Buffer.h"

#include <glad/glad.h>

namespace Mn {

    class Vao {
    public:
        Vao();

        void Create();

        [[nodiscard]] GLuint Id() const;

        void Connect(
                Buffer buffer,
                ShaderProgram shader,
                const std::string &attribute,
                GLint size,
                GLsizei stride,
                const void *pointer
        ) const;

        void Activate() const;

        static void Deactivate();

        void Draw(GLenum mode, GLint first, GLsizei count) const;

        void Draw(GLenum mode, GLsizei count, GLenum type, const void *indices) const;

        void Release() const;

    private:
        GLuint id_{};
    };

}

#endif //INCLUDED_MN_CORE_VAO_H
