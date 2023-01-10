//
// Created by ivan on 8.1.2023..
//

#ifndef OPENGL_EXAMPLES_SURFACEMATERIAL_H
#define OPENGL_EXAMPLES_SURFACEMATERIAL_H

#include <glad/glad.h>
#include <string>
#include "Material.h"
#include "BasicMaterial.h"

class SurfaceMaterial : public BasicMaterial
{
public:
    SurfaceMaterial()
    {
        drawStyle = GL_TRIANGLES;
        addRenderSetting("doubleSide", 1.0f, true);
        addRenderSetting("wireframe",  1.0f, false);
        addRenderSetting("lineWidth",  1.0f, true);
    }
};

#endif // OPENGL_EXAMPLES_SURFACEMATERIAL_H
