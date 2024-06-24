#ifndef DGF_GRAPHICS_GEOMETRY_PLANE_GEOMETRY_H
#define DGF_GRAPHICS_GEOMETRY_PLANE_GEOMETRY_H

#include "SurfaceGeometry.h"

class PlaneGeometry : public SurfaceGeometry {
public:
    PlaneGeometry();

    explicit PlaneGeometry(
            float width, float height,
            int widthSegments, int heightSegments
    );

    glm::vec3 surface(float u, float v) override;
};

#endif //DGF_GRAPHICS_GEOMETRY_PLANE_GEOMETRY_H
