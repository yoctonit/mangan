#ifndef INCLUDED_MN_GRAPHICS_SHADER_INFO_H
#define INCLUDED_MN_GRAPHICS_SHADER_INFO_H

#include <unordered_map>
#include <string>
#include "Shader.h"
#include "Attribute.h"
#include "Uniform.h"

namespace Mn {

    class ShaderInfo {
    public:
        enum class AttributeType {
            Position, Normal, TexCoord, Color
        };

        ShaderInfo();

        explicit ShaderInfo(const Shader &shader);

        ShaderInfo(const std::string &vsFile, const std::string &fsFile);

        Uniform &operator[](const std::string &name);

        [[nodiscard]] bool HasUniform(const std::string &name) const;

        [[nodiscard]] int Location(AttributeType type) const;

        [[nodiscard]] int Location(const std::string &attributeName) const;

        void Upload() const;

        void Debug() const;

    private:
        Mn::Shader mShader{};

        // Store Uniform objects, indexed by name of associated variable in shader.
        std::unordered_map<std::string, Uniform> mUniforms;

        // Store Attribute objects, indexed by name of the associated variable in shader.
        std::unordered_map<std::string, Attribute> mAttributes;

        // std::string mPositionAttributeName;
        // std::string mNormalAttributeName;
        // std::string mTexCoordAttributeName;
        // std::string mColorAttributeName;

        static std::string AttributeTypeName(AttributeType type);

        void ParseUniforms();

        void ParseAttributes();
    };

    ShaderInfo BasicMvpColorShader();

    ShaderInfo BasicLightingShader();

    ShaderInfo LightingMapsShader();

}

#endif //INCLUDED_MN_GRAPHICS_SHADER_INFO_H
