#ifndef DGF_GRAPHICS_GEOMETRY_PYRAMID_GEOMETRY_H
#define DGF_GRAPHICS_GEOMETRY_PYRAMID_GEOMETRY_H

#include "CylindricalGeometry.h"

class PyramidGeometry : public CylindricalGeometry {
public:
    PyramidGeometry();

    PyramidGeometry(
            float radius, float height,
            int sides, int heightSegments, bool closed
    );
};

#endif //DGF_GRAPHICS_GEOMETRY_PYRAMID_GEOMETRY_H
