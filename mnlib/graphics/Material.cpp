#include "Material.h"

namespace Mn {

    void Material::Create(const std::string &vsFile, const std::string &fsFile) {
        mShader = Shader::FromFiles(vsFile, fsFile);
    }

//    void Material::Create() {}

    void Material::Release() {
        mShader.Release();
    }

    void Material::AddUniform(const std::string &name, Uniform::Type type) {
        mUniforms[name] = Uniform(mShader.Locate(name), type);
    }

    Uniform &Material::operator[](const std::string &name) {
//        if (!HasUniform(name)) {
//            std::cerr << "No uniform " << name << " in material.\n";
//        }
        return mUniforms[name];
    }

    bool Material::HasUniform(const std::string &name) const {
        return mUniforms.find(name) != mUniforms.end();
    }

    void Material::AddAttribute(int location, Attribute::DataType dataType, AttributeType type) {
        std::string defaultName = AttributeTypeName(type);
        mAttributes[defaultName] = Attribute(location, dataType);
    }

    void Material::AddAttribute(const std::string &name, Attribute::DataType dataType, AttributeType type) {
        std::string defaultName = AttributeTypeName(type);
        mAttributes[defaultName] = Attribute(mShader.LocateAttribute(name), dataType);
    }

    void Material::AddAttribute(const std::string &name, Attribute::DataType dataType) {
        mAttributes[name] = Attribute(mShader.LocateAttribute(name), dataType);
    }

    int Material::Location(AttributeType type) const {
        std::string defaultName = AttributeTypeName(type);
        auto attr = mAttributes.at(defaultName);
        return attr.Location();
    }

    int Material::Location(const std::string &attributeName) const {
        auto attr = mAttributes.at(attributeName);
        return attr.Location();
    }

    void Material::Upload() const {
        mShader.Use();
        for (auto &[name, uniform]: mUniforms) {
            uniform.Upload();
        }
    }

    int Material::DrawStyle() const {
        return mDrawStyle;
    }

    void Material::DrawStyle(int drawStyle) {
        mDrawStyle = drawStyle;
    }

    std::string Material::AttributeTypeName(AttributeType type) {
        std::string defaultName;
        switch (type) {
            case AttributeType::Position:
                defaultName = "position";
                break;
            case AttributeType::Normal:
                defaultName = "normal";
                break;
            case AttributeType::TexCoord:
                defaultName = "texCoord";
                break;
            case AttributeType::Color:
                defaultName = "color";
                break;
        }
        return defaultName;
    }


    ////////////////////
    // Factory functions
    ////////////////////

    Material BasicMvpColorMaterial() {
        Material material;
        material.Create(
                "shader/basic_mvp.vs",
                "shader/basic_color.fs"
        );

        material.AddUniform("uModel", Uniform::Type::Mat4x4);
        material.AddUniform("uView", Uniform::Type::Mat4x4);
        material.AddUniform("uProjection", Uniform::Type::Mat4x4);
        material.AddUniform("uColor", Uniform::Type::Vec3);

        material.AddAttribute(0, Attribute::DataType::Vec3, Material::AttributeType::Position);

        return material;
    }

    Material BasicLightingMaterial() {
        Material material;
        material.Create(
                "shader/basic_lighting.vs",
                "shader/basic_lighting.fs"
        );

        material.AddUniform("uModel", Uniform::Type::Mat4x4);
        material.AddUniform("uView", Uniform::Type::Mat4x4);
        material.AddUniform("uProjection", Uniform::Type::Mat4x4);

        material.AddUniform("uViewPosition", Uniform::Type::Vec3);

        material.AddUniform("uMaterial.ambient", Uniform::Type::Vec3);
        material.AddUniform("uMaterial.diffuse", Uniform::Type::Vec3);
        material.AddUniform("uMaterial.specular", Uniform::Type::Vec3);
        material.AddUniform("uMaterial.shininess", Uniform::Type::Float);

        material.AddUniform("uLight.position", Uniform::Type::Vec3);
        material.AddUniform("uLight.ambient", Uniform::Type::Vec3);
        material.AddUniform("uLight.diffuse", Uniform::Type::Vec3);
        material.AddUniform("uLight.specular", Uniform::Type::Vec3);

        material.AddAttribute(0, Attribute::DataType::Vec3, Material::AttributeType::Position);
        material.AddAttribute(1, Attribute::DataType::Vec3, Material::AttributeType::Normal);

        return material;
    }

    Material LightingMapsMaterial() {
        Material material;
        material.Create(
                "shader/lighting_maps.vs",
                "shader/lighting_maps.fs"
        );

        material.AddUniform("uModel", Uniform::Type::Mat4x4);
        material.AddUniform("uView", Uniform::Type::Mat4x4);
        material.AddUniform("uProjection", Uniform::Type::Mat4x4);

        material.AddUniform("uViewPosition", Uniform::Type::Vec3);

        material.AddUniform("uMaterial.diffuse", Uniform::Type::Int);
        material.AddUniform("uMaterial.specular", Uniform::Type::Int);
        material.AddUniform("uMaterial.shininess", Uniform::Type::Float);

        material.AddUniform("uLight.position", Uniform::Type::Vec3);
        material.AddUniform("uLight.ambient", Uniform::Type::Vec3);
        material.AddUniform("uLight.diffuse", Uniform::Type::Vec3);
        material.AddUniform("uLight.specular", Uniform::Type::Vec3);

        material.AddAttribute(0, Attribute::DataType::Vec3, Material::AttributeType::Position);
        material.AddAttribute(1, Attribute::DataType::Vec3, Material::AttributeType::Normal);
        material.AddAttribute(2, Attribute::DataType::Vec2, Material::AttributeType::TexCoord);

        return material;
    }
}
