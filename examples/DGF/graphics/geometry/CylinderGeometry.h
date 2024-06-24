#ifndef DGF_GRAPHICS_GEOMETRY_CYLINDER_GEOMETRY_H
#define DGF_GRAPHICS_GEOMETRY_CYLINDER_GEOMETRY_H

#include "CylindricalGeometry.h"

class CylinderGeometry : public CylindricalGeometry {
public:
    CylinderGeometry();

    CylinderGeometry(
            float radius, float height,
            int radialSegments, int heightSegments, bool closed
    );
};

#endif //DGF_GRAPHICS_GEOMETRY_CYLINDER_GEOMETRY_H
