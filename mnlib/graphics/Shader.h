#ifndef INCLUDED_MN_GRAPHICS_SHADER_H
#define INCLUDED_MN_GRAPHICS_SHADER_H

#include <glad/glad.h>
#include <string>
#include <unordered_map>

namespace Mn {

    class Shader {
    public:
//        static Shader FromFiles(
//                const std::string &vertexShaderFile,
//                const std::string &fragmentShaderFile
//        );

        Shader();

        Shader(
                const std::string &vertexShaderFile,
                const std::string &fragmentShaderFile
        );

        ~Shader();

        Shader(const Shader &other);

        Shader &operator=(const Shader &other);

        [[nodiscard]] unsigned int Id() const;

        void Use() const;

        [[nodiscard]] int Locate(const std::string &name) const;

        // [[nodiscard]] int LocateAttribute(const std::string &attributeName) const;

        void Debug(const std::string &msg) const;

        static void DebugRefCnt();

    private:
        unsigned int mId{};

        static std::string LoadFile(const std::string &fileName);

        static unsigned int Compile(const std::string &shaderSource, GLenum shaderType);

        static unsigned int Link(unsigned int vertexShaderId, unsigned int fragmentShaderId);

        //////////////////////
        // Reference count map
        //////////////////////
        static std::unordered_map<unsigned int, int> mRefCnt;

        void IncRef() const;

        [[nodiscard]] int DecRef() const;
    };

}

#endif // INCLUDED_MN_GRAPHICS_SHADER_H
