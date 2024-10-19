//
// Created by ivan on 8.1.2023..
//

#ifndef INCLUDED_MN_LINE_MATERIAL_H
#define INCLUDED_MN_LINE_MATERIAL_H

#include "glad/glad.h"
#include <string>
#include "Material.h"
#include "BasicMaterial.h"

class LineMaterial : public BasicMaterial {
public:
    LineMaterial() : BasicMaterial() {
        drawStyle = GL_LINES;
        addRenderSetting("lineWidth", 1.0f, true);
    }

    explicit LineMaterial(const std::string &lineStyle) : BasicMaterial() {
        if (lineStyle == "segments")
            drawStyle = GL_LINES;
        else if (lineStyle == "connected")
            drawStyle = GL_LINE_STRIP;
        else if (lineStyle == "loop")
            drawStyle = GL_LINE_LOOP;
        else {
            std::cout << "Unknown line style: " << lineStyle << "\n";
            drawStyle = GL_LINES;
        }
        addRenderSetting("lineWidth", 1.0, true);
    }
};

#endif //INCLUDED_MN_LINE_MATERIAL_H
