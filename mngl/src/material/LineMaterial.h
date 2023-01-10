//
// Created by ivan on 8.1.2023..
//

#ifndef OPENGL_EXAMPLES_LINEMATERIAL_H
#define OPENGL_EXAMPLES_LINEMATERIAL_H

#include <glad/glad.h>
#include <string>
#include "Material.h"
#include "BasicMaterial.h"

class LineMaterial : public BasicMaterial {
public:
    LineMaterial() {
        drawStyle = GL_LINES;
        addRenderSetting("lineWidth", 1.0f, true);
    }

    LineMaterial(const std::string& lineStyle) {
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

#endif //OPENGL_EXAMPLES_LINEMATERIAL_H
