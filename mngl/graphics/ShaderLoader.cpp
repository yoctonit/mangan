#include <iostream>
#include "ShaderLoader.h"

namespace Mn {

    ShaderLoader::ShaderLoader(const Shader &shader) : mShader{shader} {}

    ShaderLoader::ShaderLoader(const std::string &vsFile, const std::string &fsFile)
            : mShader{vsFile, fsFile} {}

    void ShaderLoader::Use() const {
        mShader.Use();
    }

    void ShaderLoader::Set(const std::string &name, bool value) const {
        glUniform1i(LocateUniform(name), (int) value);
    }

    void ShaderLoader::Set(const std::string &name, int value) const {
        glUniform1i(LocateUniform(name), value);
    }

    void ShaderLoader::Set(const std::string &name, float value) const {
        glUniform1f(LocateUniform(name), value);
    }

    void ShaderLoader::Set(const std::string &name, const glm::vec2 &value) const {
        glUniform2fv(LocateUniform(name), 1, &value[0]);
    }

    void ShaderLoader::Set(const std::string &name, float x, float y) const {
        glUniform2f(LocateUniform(name), x, y);
    }

    void ShaderLoader::Set(const std::string &name, const glm::vec3 &value) const {
        glUniform3fv(LocateUniform(name), 1, &value[0]);
    }

    void ShaderLoader::Set(const std::string &name, float x, float y, float z) const {
        glUniform3f(LocateUniform(name), x, y, z);
    }

    void ShaderLoader::Set(const std::string &name, const glm::vec4 &value) const {
        glUniform4fv(LocateUniform(name), 1, &value[0]);
    }

    void ShaderLoader::Set(const std::string &name, float x, float y, float z, float w) const {
        glUniform4f(LocateUniform(name), x, y, z, w);
    }

    void ShaderLoader::Set(const std::string &name, const glm::mat2 &mat) const {
        glUniformMatrix2fv(LocateUniform(name), 1, GL_FALSE, &mat[0][0]);
    }

    void ShaderLoader::Set(const std::string &name, const glm::mat3 &mat) const {
        glUniformMatrix3fv(LocateUniform(name), 1, GL_FALSE, &mat[0][0]);
    }

    void ShaderLoader::Set(const std::string &name, const glm::mat4 &mat) const {
        glUniformMatrix4fv(LocateUniform(name), 1, GL_FALSE, &mat[0][0]);
    }

    int ShaderLoader::LocateUniform(const std::string &name) const {
        int uniformRef = glGetUniformLocation(mShader.Id(), name.c_str());
        if (uniformRef == -1) {
            std::cerr << "Uniform " << name << " not found in shader " << mShader.Id() << ".\n";
        }
        return uniformRef;
    }

}
