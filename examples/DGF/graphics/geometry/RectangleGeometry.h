#ifndef DGF_GRAPHICS_GEOMETRY_RECTANGLE_GEOMETRY_H
#define DGF_GRAPHICS_GEOMETRY_RECTANGLE_GEOMETRY_H

#include "Geometry.h"

class RectangleGeometry : public Geometry {
public:
    RectangleGeometry();

    RectangleGeometry(float width, float height);
};

#endif //DGF_GRAPHICS_GEOMETRY_RECTANGLE_GEOMETRY_H
