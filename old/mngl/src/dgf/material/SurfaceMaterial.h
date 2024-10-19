//
// Created by ivan on 8.1.2023..
//

#ifndef INCLUDED_MN_SURFACE_MATERIAL_H
#define INCLUDED_MN_SURFACE_MATERIAL_H

#include "glad/glad.h"
#include <string>
#include "Material.h"
#include "BasicMaterial.h"

class SurfaceMaterial : public BasicMaterial {
public:
    SurfaceMaterial() : BasicMaterial() {
        drawStyle = GL_TRIANGLES;
        addRenderSetting("doubleSide", 1.0f, true);
        addRenderSetting("wireframe", 1.0f, false);
        addRenderSetting("lineWidth", 1.0f, true);
    }
};

#endif // INCLUDED_MN_SURFACE_MATERIAL_H
