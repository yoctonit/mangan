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

//    Uniform &Material::GetUniform(const std::string &name) {
//        if (!HasUniform(name)) {
//            std::cerr << "No uniform " << name << " in material.\n";
//        }
//        return mUniforms[name];
//    }

    Uniform &Material::operator[](const std::string &name) {
//        if (!HasUniform(name)) {
//            std::cerr << "No uniform " << name << " in material.\n";
//        }
        return mUniforms[name];
    }

    bool Material::HasUniform(const std::string &name) const {
        return mUniforms.find(name) != mUniforms.end();
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

        return material;
    }

}