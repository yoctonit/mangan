#ifndef DGF_GRAPHICS_EXTRAS_GRID_GEOMETRY_H
#define DGF_GRAPHICS_EXTRAS_GRID_GEOMETRY_H

#include "../geometry/Geometry.h"

class GridGeometry : public Geometry {
public:
    GridGeometry();

    GridGeometry(
            float size, int divisions,
            glm::vec3 gridColor, glm::vec3 centerColor
    );
};

#endif //DGF_GRAPHICS_EXTRAS_GRID_GEOMETRY_H
