#ifndef DGF_GRAPHICS_GEOMETRY_HEXAGON_GEOMETRY_H
#define DGF_GRAPHICS_GEOMETRY_HEXAGON_GEOMETRY_H

#include "PolygonGeometry.h"

class HexagonGeometry : public PolygonGeometry {
public:
    HexagonGeometry();

    explicit HexagonGeometry(float radius);
};

#endif //DGF_GRAPHICS_GEOMETRY_HEXAGON_GEOMETRY_H
