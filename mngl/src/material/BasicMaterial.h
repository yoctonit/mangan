//
// Created by ivan on 8.1.2023..
//

#ifndef OPENGL_EXAMPLES_BASICMATERIAL_H
#define OPENGL_EXAMPLES_BASICMATERIAL_H

#include <glm/glm.hpp>
#include "Material.h"
#include "Uniform.h"

class BasicMaterial : public Material {
public:
    BasicMaterial() : Material("shader/BasicMaterial.vert", "shader/BasicMaterial.frag") {
        addUniform("baseColor", std::make_shared<Mn::Shader::Uniform>());
        addUniform("useVertexColors", std::make_shared<Mn::Shader::Uniform>());
        // addUniform("vec3", "baseColor", 1.0f /*glm::vec3(1.0f, 1.0f, 1.0f)*/, true);
        // addUniform("bool", "useVertexColors", 0.0f, true);
        locateUniforms();
    }
};

#endif //OPENGL_EXAMPLES_BASICMATERIAL_H
