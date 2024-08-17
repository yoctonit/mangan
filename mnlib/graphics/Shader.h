#ifndef INCLUDED_MN_GRAPHICS_SHADER_H
#define INCLUDED_MN_GRAPHICS_SHADER_H

#include <glad/glad.h>
#include <string>

namespace Mn {

    class Shader {
    public:
        static Shader FromFiles(
                const std::string &vertexShaderFile,
                const std::string &fragmentShaderFile
        );

        [[nodiscard]] unsigned int Id() const;

        void Use() const;

        void Release();

        [[nodiscard]] int Locate(const std::string &uniformName) const;

        void Debug(const std::string &msg) const;

    private:
        unsigned int m_id{};

        static std::string LoadFile(const std::string &fileName);

        static unsigned int Compile(const std::string &shaderSource, GLenum shaderType);

        static unsigned int Link(unsigned int vertexShaderId, unsigned int fragmentShaderId);

    };

}

#endif // INCLUDED_MN_GRAPHICS_SHADER_H
