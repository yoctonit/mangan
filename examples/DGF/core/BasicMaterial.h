//
// Created by ivan on 8.1.2023..
//

#ifndef OPENGL_EXAMPLES_BASICMATERIAL_H
#define OPENGL_EXAMPLES_BASICMATERIAL_H

#include "Material.h"

class BasicMaterial : public Material {
public:
    BasicMaterial() : Material() {
        super(
                "./src/material/BasicMaterial.vert",
                "./src/material/BasicMaterial.frag");
        addUniform("vec3", "baseColor", new Vector(1, 1, 1));
        addUniform("bool", "useVertexColors", 0);
        locateUniforms();
    }
};

#endif //OPENGL_EXAMPLES_BASICMATERIAL_H
