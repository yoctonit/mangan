#ifndef DGF_GRAPHICS_GEOMETRY_RECTANGLE_GEOMETRY_H
#define DGF_GRAPHICS_GEOMETRY_RECTANGLE_GEOMETRY_H

#include <glm/vec2.hpp>
#include "Geometry.h"

class RectangleGeometry : public Geometry {
public:
    RectangleGeometry();

    RectangleGeometry(float width, float height);

    RectangleGeometry(float width, float height, glm::vec2 position, glm::vec2 alignment);
};

#endif //DGF_GRAPHICS_GEOMETRY_RECTANGLE_GEOMETRY_H
