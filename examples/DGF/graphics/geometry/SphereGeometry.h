#ifndef DGF_GRAPHICS_GEOMETRY_SPHERE_GEOMETRY_H
#define DGF_GRAPHICS_GEOMETRY_SPHERE_GEOMETRY_H

#include "EllipsoidGeometry.h"


class SphereGeometry : public EllipsoidGeometry {
public:
    SphereGeometry();

    explicit SphereGeometry(float radius);

    SphereGeometry(float radius, int radiusSegments, int heightSegments);

//    glm::vec3 surface(float u, float v) override;

//private:
//    float m_radius;
};

#endif //DGF_GRAPHICS_GEOMETRY_SPHERE_GEOMETRY_H
