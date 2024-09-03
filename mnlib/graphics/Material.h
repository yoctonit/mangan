#ifndef INCLUDED_MN_GRAPHICS_MATERIAL_H
#define INCLUDED_MN_GRAPHICS_MATERIAL_H

#include <map>
#include <string>
#include "../graphics/Shader.h"
#include "../graphics/Attribute.h"
#include "../graphics/Uniform.h"

namespace Mn {

    class Material {
    public:
        enum class AttributeType {
            Position, Normal, TexCoord, Color
        };

        void Create(const std::string &vsFile, const std::string &fsFile);

        void Release();

        void AddUniform(const std::string &name, Uniform::Type type);

        Uniform &operator[](const std::string &name);

        [[nodiscard]] bool HasUniform(const std::string &name) const;

        void AddAttribute(int location, Attribute::DataType dataType, AttributeType type);

        void AddAttribute(const std::string &name, Attribute::DataType dataType, AttributeType type);

        void AddAttribute(const std::string &name, Attribute::DataType dataType);

        [[nodiscard]] int Location(AttributeType type) const;

        [[nodiscard]] int Location(const std::string &attributeName) const;

        void Upload() const;

        [[nodiscard]] int DrawStyle() const;

        void DrawStyle(int drawStyle);

    protected:
        Mn::Shader mShader{};
        int mDrawStyle{GL_TRIANGLES};

        // Store Uniform objects, indexed by name of associated variable in shader.
        std::map<std::string, Uniform> mUniforms;

        // Store Attribute objects, indexed by predefined AttributeType
        // or by name of the associated variable in shader.
        std::map<std::string, Attribute> mAttributes;

        static std::string AttributeTypeName(AttributeType type);
    };

    Material BasicMvpColorMaterial();

    Material BasicLightingMaterial();

    Material LightingMapsMaterial();

}

#endif //INCLUDED_MN_GRAPHICS_MATERIAL_H
