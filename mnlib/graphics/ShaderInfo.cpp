#include <iostream>
#include "ShaderInfo.h"

namespace Mn {

    ShaderInfo::ShaderInfo() = default;

    ShaderInfo::ShaderInfo(const Shader &shader) : mShader{shader} {
        ParseUniforms();
        ParseAttributes();
    }

    ShaderInfo::ShaderInfo(const std::string &vsFile, const std::string &fsFile) {
        mShader = {vsFile, fsFile};
        ParseUniforms();
        ParseAttributes();
    }

//    void ShaderInfo::AddUniform(const std::string &name, int type) {
//        mUniforms[name] = Uniform(mShader.Locate(name), type);
//    }

    Uniform &ShaderInfo::operator[](const std::string &name) {
//        if (!HasUniform(name)) {
//            std::cerr << "No uniform " << name << " in shader.\n";
//        }
        return mUniforms[name];
    }

    bool ShaderInfo::HasUniform(const std::string &name) const {
        return mUniforms.find(name) != mUniforms.end();
    }

//    void ShaderInfo::AddAttribute(int location, Attribute::DataType dataType, AttributeType type) {
//        std::string defaultName = AttributeTypeName(type);
//        mAttributes[defaultName] = Attribute(location, dataType);
//    }
//
//    void ShaderInfo::AddAttribute(const std::string &name, Attribute::DataType dataType, AttributeType type) {
//        std::string defaultName = AttributeTypeName(type);
//        mAttributes[defaultName] = Attribute(mShader.Locate(name), dataType);
//    }
//
//    void ShaderInfo::AddAttribute(const std::string &name, Attribute::DataType dataType) {
//        mAttributes[name] = Attribute(mShader.Locate(name), dataType);
//    }

    int ShaderInfo::Location(AttributeType type) const {
        std::string defaultName = AttributeTypeName(type);
        auto attr = mAttributes.at(defaultName);
        return attr.Location();
    }

    int ShaderInfo::Location(const std::string &attributeName) const {
        auto attr = mAttributes.at(attributeName);
        return attr.Location();
    }

    void ShaderInfo::Upload() const {
        mShader.Use();
        for (auto &[name, uniform]: mUniforms) {
            uniform.Upload();
        }
    }

//    int ShaderInfo::DrawStyle() const {
//        return mDrawStyle;
//    }
//
//    void ShaderInfo::DrawStyle(int drawStyle) {
//        mDrawStyle = drawStyle;
//    }

    void ShaderInfo::ParseUniforms() {
        int numberOfUniforms;
        glGetProgramInterfaceiv(mShader.Id(), GL_UNIFORM, GL_ACTIVE_RESOURCES, &numberOfUniforms);

        GLenum properties[] = {GL_NAME_LENGTH, GL_TYPE, GL_LOCATION, GL_BLOCK_INDEX};

        for (int i = 0; i < numberOfUniforms; ++i) {
            int results[4];
            glGetProgramResourceiv(mShader.Id(), GL_UNIFORM, i, 4, properties, 4, nullptr, results);

            if (results[3] != -1) {
                std::cout << "skip uniforms in blocks\n";
                continue; // skip uniforms in blocks
            }

            GLint nameBufferSize = results[0];
            // GLint nameBufferSize = results[0] + 1;
            char *name = new char[nameBufferSize];
            glGetProgramResourceName(mShader.Id(), GL_UNIFORM, i, nameBufferSize, nullptr, name);

            mUniforms[std::string(name)] = Uniform(results[2], results[1]);
            delete[] name;
        }
    }

    void ShaderInfo::ParseAttributes() {
        GLint numberOfAttributes;
        glGetProgramInterfaceiv(mShader.Id(), GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &numberOfAttributes);

        GLenum properties[] = {GL_NAME_LENGTH, GL_TYPE, GL_LOCATION};

        for (int i = 0; i < numberOfAttributes; ++i) {
            GLint results[3];
            glGetProgramResourceiv(mShader.Id(), GL_PROGRAM_INPUT, i, 3, properties, 3, nullptr, results);

            GLint nameBufferSize = results[0];
            // GLint nameBufferSize = results[0] + 1;
            char *name = new char[nameBufferSize];
            glGetProgramResourceName(mShader.Id(), GL_PROGRAM_INPUT, i, nameBufferSize, nullptr, name);

            // std::string string_name(name);
            mAttributes[std::string(name)] = Attribute(results[2], results[1]);
            delete[] name;
        }
    }

    void ShaderInfo::Debug() const {
        std::cout << "Number of found uniforms: " << mUniforms.size() << '\n';
//        std::cout << "Uniform Name\t\tInfo\n";
//        for (const auto &uniform: mUniforms) {
//            uniform.second.Debug(uniform.first);
//        }
        std::cout << "Attribute\tInfo\n--------------------\n";
        for (const auto &attribute: mAttributes) {
            attribute.second.Debug(attribute.first);
        }
    }

    std::string ShaderInfo::AttributeTypeName(AttributeType type) {
        std::string defaultName;
        switch (type) {
            case AttributeType::Position:
                defaultName = "aPosition";
                break;
            case AttributeType::Normal:
                defaultName = "aNormal";
                break;
            case AttributeType::TexCoord:
                defaultName = "aTexCoord";
                break;
            case AttributeType::Color:
                defaultName = "aColor";
                break;
        }
        return defaultName;
    }

    ////////////////////
    // Factory functions
    ////////////////////

    ShaderInfo BasicMvpColorShader() {
        ShaderInfo material{"shader/basic_mvp.vs", "shader/basic_color.fs"};
        return material;
    }

    ShaderInfo BasicLightingShader() {
        ShaderInfo material{"shader/basic_lighting.vs", "shader/basic_lighting.fs"};
        return material;
    }

    ShaderInfo LightingMapsShader() {
        ShaderInfo material{"shader/lighting_maps.vs", "shader/lighting_maps.fs"};
        return material;
    }
}
