#ifndef INCLUDED_MN_CORE_SHADER_H
#define INCLUDED_MN_CORE_SHADER_H

#include <glad/glad.h>
#include <string>
#include <unordered_map>

namespace Mn {

    class Shader {
    public:
        Shader();

        Shader(
                const std::string &vertexShaderFile,
                const std::string &fragmentShaderFile
        );

        Shader(
                const std::string &vertexShaderFile,
                const std::string &fragmentShaderFile,
                const std::string &geometryShaderFile
        );

        ~Shader();

        Shader(const Shader &other);

        Shader &operator=(const Shader &other);

        [[nodiscard]] unsigned int Id() const;

        void Use() const;

        [[nodiscard]] int Locate(const std::string &name) const;

        void Debug(const std::string &msg) const;

        static void DebugRefCnt();

    private:
        unsigned int mId{};

        static std::string LoadFile(const std::string &fileName);

        static unsigned int Compile(const std::string &shaderSource, GLenum shaderType);

        static unsigned int Link(unsigned int vertexShaderId, unsigned int fragmentShaderId);

        static unsigned int Link(
                unsigned int vertexShaderId,
                unsigned int fragmentShaderId,
                unsigned int geometryShaderId
        );

        //////////////////////
        // Reference count map
        //////////////////////
        static std::unordered_map<unsigned int, int> mRefCnt;

        void IncRef() const;

        [[nodiscard]] int DecRef() const;
    };

}

#endif // INCLUDED_MN_CORE_SHADER_H
