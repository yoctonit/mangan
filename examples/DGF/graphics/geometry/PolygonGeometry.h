#ifndef DGF_GRAPHICS_GEOMETRY_POLYGON_GEOMETRY_H
#define DGF_GRAPHICS_GEOMETRY_POLYGON_GEOMETRY_H

#include "Geometry.h"

class PolygonGeometry : public Geometry {
public:
    PolygonGeometry();

    PolygonGeometry(int sides, float radius);
};

#endif //DGF_GRAPHICS_GEOMETRY_POLYGON_GEOMETRY_H
