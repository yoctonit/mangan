#ifndef DGF_GRAPHICS_GEOMETRY_CYLINDRICAL_GEOMETRY_H
#define DGF_GRAPHICS_GEOMETRY_CYLINDRICAL_GEOMETRY_H

#include "SurfaceGeometry.h"


class CylindricalGeometry : public SurfaceGeometry {
public:
    CylindricalGeometry();

    CylindricalGeometry(
            float radiusTop, float radiusBottom, float height,
            int radialSegments, int heightSegments,
            bool closedTop, bool closedBottom
    );

    glm::vec3 surface(float u, float v) override;

private:
    float m_radiusTop;
    float m_radiusBottom;
    float m_height;
//    bool m_closedTop;
//    bool m_closedBottom;
};

#endif //DGF_GRAPHICS_GEOMETRY_CYLINDRICAL_GEOMETRY_H
