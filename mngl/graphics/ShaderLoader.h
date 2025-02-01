#ifndef INCLUDED_MN_GRAPHICS_SHADER_LOADER_H
#define INCLUDED_MN_GRAPHICS_SHADER_LOADER_H

#include <string>
#include "../core/Shader.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>


namespace Mn {

    class ShaderLoader {
    public:
        explicit ShaderLoader(const Shader &shader);

        ShaderLoader(const std::string &vsFile, const std::string &fsFile);

        void Use() const;

        void Set(const std::string &name, bool value) const;

        void Set(const std::string &name, int value) const;

        void Set(const std::string &name, float value) const;

        void Set(const std::string &name, const glm::vec2 &value) const;

        void Set(const std::string &name, float x, float y) const;

        void Set(const std::string &name, const glm::vec3 &value) const;

        void Set(const std::string &name, float x, float y, float z) const;

        void Set(const std::string &name, const glm::vec4 &value) const;

        void Set(const std::string &name, float x, float y, float z, float w) const;

        void Set(const std::string &name, const glm::mat2 &mat) const;

        void Set(const std::string &name, const glm::mat3 &mat) const;

        void Set(const std::string &name, const glm::mat4 &mat) const;

    private:
        Mn::Shader mShader{};

        [[nodiscard]] int LocateUniform(const std::string &name) const;
    };

}

#endif //INCLUDED_MN_GRAPHICS_SHADER_LOADER_H
