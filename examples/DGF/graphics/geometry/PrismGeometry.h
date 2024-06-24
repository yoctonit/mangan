#ifndef DGF_GRAPHICS_GEOMETRY_PRISM_GEOMETRY_H
#define DGF_GRAPHICS_GEOMETRY_PRISM_GEOMETRY_H

#include "CylindricalGeometry.h"

class PrismGeometry : public CylindricalGeometry {
public:
    PrismGeometry();

    PrismGeometry(
            float radius, float height,
            int sides, int heightSegments, bool closed
    );
};

#endif //DGF_GRAPHICS_GEOMETRY_PRISM_GEOMETRY_H
