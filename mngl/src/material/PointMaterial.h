//
// Created by ivan on 8.1.2023..
//

#ifndef INCLUDED_MN_POINT_MATERIAL_H
#define INCLUDED_MN_POINT_MATERIAL_H

#include <glad/glad.h>
#include <string>
#include "Material.h"
#include "BasicMaterial.h"

class PointMaterial : public BasicMaterial {
public:
    PointMaterial() : BasicMaterial() {
        drawStyle = GL_POINTS;
        addRenderSetting("pointSize", 16.0f, true);
        addRenderSetting("roundedPoints", 1.0f, true);
    }
};

#endif //INCLUDED_MN_POINT_MATERIAL_H
