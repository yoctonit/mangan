//
// Created by ivan on 8.1.2023..
//

#ifndef INCLUDED_MN_MATERIAL_H
#define INCLUDED_MN_MATERIAL_H

#include <glm/glm.hpp>
#include <string>
#include <map>
#include <memory>
#include "../Shader.h"
#include "../Uniform.h"
#include "../RenderSetting.h"

class Material {
public:
    GLuint programRef{};

    int drawStyle{};

    // Store Mn::Uniform objects,
    // indexed by name of associated variable in shader.
    std::map<std::string, Mn::Shader::Uniform> uniforms;

    // Store OpenGL render settings,
    // indexed by variable name.
    // Additional settings added by extending classes.
    std::map<std::string, RenderSetting> renderSettings;

//    Material() = default;

    Material(const std::string &vertexShaderFileName, const std::string &fragmentShaderFileName) {
        programRef = Mn::Shader::CreateFromFiles(vertexShaderFileName, fragmentShaderFileName);

        drawStyle = GL_TRIANGLES;

        // Each shader typically contains these uniforms;
        // values set during render process from Mesh/Camera.
        // Additional uniforms added by extending classes.
        addUniform("modelMatrix", Mn::Shader::Uniform());
        addUniform("viewMatrix", Mn::Shader::Uniform());
        addUniform("projectionMatrix", Mn::Shader::Uniform());
    }

    void addUniform(const std::string &variableName, Mn::Shader::Uniform uniform) {
        uniform.init(programRef, variableName);
        uniforms[variableName] = uniform;
    }

    // initialize all uniform variable references
    void locateUniforms() {
        for (const auto &myPair: uniforms) {
            std::string variableName = myPair.first;
            uniforms[variableName].init(programRef, variableName);
            //            uniform.locateVariable(programRef, variableName);
        }
    }

    virtual void uploadUniforms() {}

    void baseColor(glm::vec3 bc) {
        _baseColor = bc;
    }

    void useVertexColors(bool flag) {
        _useVertexColors = flag;
    }

    void addRenderSetting(const std::string &settingName, float fData, bool lData) {
        renderSettings[settingName] = RenderSetting(settingName, fData, lData);
    }
protected:
    glm::vec3 _baseColor;
    bool _useVertexColors;
};

#endif // INCLUDED_MN_MATERIAL_H
