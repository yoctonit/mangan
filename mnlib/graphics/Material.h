#ifndef INCLUDED_MN_GRAPHICS_MATERIAL_H
#define INCLUDED_MN_GRAPHICS_MATERIAL_H

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

        // [[nodiscard]] Uniform &GetUniform(const std::string &name);

        Uniform &operator[](const std::string &name);

        [[nodiscard]] bool HasUniform(const std::string &name) const;

        void Upload() const;

        [[nodiscard]] int DrawStyle() const;

        void DrawStyle(int drawStyle);

    protected:
        Mn::Shader mShader{};
        int mDrawStyle{GL_TRIANGLES};

        // Store Uniform objects, indexed by name of associated variable in shader.
        std::map<std::string, Uniform> mUniforms;
    };

    Material BasicMvpColorMaterial();

    Material BasicLightingMaterial();

}

#endif //INCLUDED_MN_GRAPHICS_MATERIAL_H
