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

    Uniform &Material::GetUniform(const std::string &name) {
//        if (!HasUniform(name)) {
//            std::cerr << "No uniform " << name << " in material.\n";
//        }
        return mUniforms[name];
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

    void Material::Upload() const {
        mShader.Use();
        for (auto &[name, uniform]: mUniforms) {
            uniform.Upload();
        }
    }

}