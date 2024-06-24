#ifndef DGF_GRAPHICS_GEOMETRY_CONE_GEOMETRY_H
#define DGF_GRAPHICS_GEOMETRY_CONE_GEOMETRY_H

#include "CylindricalGeometry.h"

class ConeGeometry : public CylindricalGeometry {
public:
    ConeGeometry();

    ConeGeometry(
            float radius, float height,
            int radialSegments, int heightSegments, bool closed
    );
};

#endif //DGF_GRAPHICS_GEOMETRY_CONE_GEOMETRY_H
