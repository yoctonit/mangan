//
// Created by ivan on 8.1.2023..
//

#ifndef INCLUDED_MN_BASIC_MATERIAL_H
#define INCLUDED_MN_BASIC_MATERIAL_H

#include "glm/glm.hpp"
#include "Material.h"
#include "Uniform.h"

class BasicMaterial : public Material {
public:
    BasicMaterial() : Material("shader/BasicMaterial.vert", "shader/BasicMaterial.frag") {
        addUniform("baseColor", Mn::Shader::Uniform());
        addUniform("useVertexColors", Mn::Shader::Uniform());
        // addUniform("vec3", "baseColor", 1.0f /*glm::vec3(1.0f, 1.0f, 1.0f)*/, true);
        // addUniform("bool", "useVertexColors", 0.0f, true);
        locateUniforms();
    }

    void uploadUniforms() override {
        Mn::Shader::UploadUniform(uniforms["baseColor"], _baseColor);
        Mn::Shader::UploadUniform(uniforms["useVertexColors"], _useVertexColors);
    }
};

#endif //INCLUDED_MN_BASIC_MATERIAL_H
