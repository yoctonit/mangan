#ifndef DGF_GRAPHICS_GEOMETRY_ELLIPSOID_GEOMETRY_H
#define DGF_GRAPHICS_GEOMETRY_ELLIPSOID_GEOMETRY_H

#include "SurfaceGeometry.h"


class EllipsoidGeometry : public SurfaceGeometry {
public:
    EllipsoidGeometry();

    EllipsoidGeometry(
            float width, float height, float depth,
            int radiusSegments, int heightSegments
    );

    glm::vec3 surface(float u, float v) override;

private:
    float m_width;
    float m_height;
    float m_depth;
};

#endif //DGF_GRAPHICS_GEOMETRY_ELLIPSOID_GEOMETRY_H
