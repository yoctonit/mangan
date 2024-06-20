#ifndef DGF_GRAPHICS_GEOMETRY_BOX_GEOMETRY_H
#define DGF_GRAPHICS_GEOMETRY_BOX_GEOMETRY_H

#include "Geometry.h"

class BoxGeometry : public Geometry {
public:
    BoxGeometry();

    BoxGeometry(float width, float height, float depth);
};

#endif //DGF_GRAPHICS_GEOMETRY_BOX_GEOMETRY_H
