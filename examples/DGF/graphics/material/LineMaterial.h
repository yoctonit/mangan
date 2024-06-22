#ifndef DGF_GRAPHICS_MATERIAL_LINE_MATERIAL_H
#define DGF_GRAPHICS_MATERIAL_LINE_MATERIAL_H

#include "BasicMaterial.h"

class LineMaterial : public BasicMaterial {
public:
    enum class LineStyle {
        Segments, Connected, Loop
    };

    LineMaterial();

    explicit LineMaterial(LineStyle style);
};

#endif //DGF_GRAPHICS_MATERIAL_LINE_MATERIAL_H
