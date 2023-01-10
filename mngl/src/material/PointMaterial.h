//
// Created by ivan on 8.1.2023..
//

#ifndef OPENGL_EXAMPLES_POINTMATERIAL_H
#define OPENGL_EXAMPLES_POINTMATERIAL_H

#include <glad/glad.h>
#include <string>
#include "Material.h"
#include "BasicMaterial.h"

class PointMaterial : public BasicMaterial {
public:
    PointMaterial() {
        drawStyle = GL_POINTS;
        addRenderSetting("pointSize", 16.0f, true);
        addRenderSetting("roundedPoints", 1.0f, true);
    }
};

#endif //OPENGL_EXAMPLES_POINTMATERIAL_H
