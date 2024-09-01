#ifndef INCLUDED_MN_MATERIAL_MATERIAL_H
#define INCLUDED_MN_MATERIAL_MATERIAL_H

#include <map>
#include <string>
#include "../graphics/Shader.h"
#include "../graphics/Uniform.h"

namespace Mn {

    class Material {
    public:
        void Create(const std::string &vsFile, const std::string &fsFile);

        void Release();

        void AddUniform(const std::string &name, Uniform::Type type);

        [[nodiscard]] Uniform &GetUniform(const std::string &name);

        Uniform &operator[](const std::string &name);

        [[nodiscard]] bool HasUniform(const std::string &name) const;

        void Upload() const;

    protected:
        Mn::Shader mShader{};

        // Store Uniform objects, indexed by name of associated variable in shader.
        std::map<std::string, Uniform> mUniforms;
    };

}

#endif //INCLUDED_MN_MATERIAL_MATERIAL_H
