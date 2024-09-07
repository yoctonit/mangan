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

        // void AddUniform(const std::string &name, int type);

        Uniform &operator[](const std::string &name);

        [[nodiscard]] bool HasUniform(const std::string &name) const;

//        void AddAttribute(int location, Attribute::DataType dataType, AttributeType type);
//
//        void AddAttribute(const std::string &name, Attribute::DataType dataType, AttributeType type);
//
//        void AddAttribute(const std::string &name, Attribute::DataType dataType);

        [[nodiscard]] int Location(AttributeType type) const;

        [[nodiscard]] int Location(const std::string &attributeName) const;

        void Upload() const;

        // [[nodiscard]] int DrawStyle() const;

        // void DrawStyle(int drawStyle);

        void Debug() const;

    private:
        Mn::Shader mShader{};
        // int mDrawStyle{GL_TRIANGLES};

        // Store Uniform objects, indexed by name of associated variable in shader.
        std::unordered_map<std::string, Uniform> mUniforms;

        // Store Attribute objects, indexed by predefined AttributeType
        // or by name of the associated variable in shader.
        std::unordered_map<std::string, Attribute> mAttributes;

        static std::string AttributeTypeName(AttributeType type);

        void ParseUniforms();

        void ParseAttributes();
    };

    ShaderInfo BasicMvpColorShader();

    ShaderInfo BasicLightingShader();

    ShaderInfo LightingMapsShader();

}

#endif //INCLUDED_MN_GRAPHICS_SHADER_INFO_H
