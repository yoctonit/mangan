#include <cmath>
#include "EllipsoidGeometry.h"

EllipsoidGeometry::EllipsoidGeometry()
        : EllipsoidGeometry(
        1.0f, 1.0f, 1.0f,
        32, 16
) {}

EllipsoidGeometry::EllipsoidGeometry(
        float width, float height, float depth,
        int radiusSegments, int heightSegments
) : SurfaceGeometry(
        0.0f, 2.0f * M_PI, radiusSegments,
        -M_PI / 2.0f, M_PI / 2.0f, heightSegments
), m_width{width}, m_height{height}, m_depth{depth} {
    calculateSurface();
}

glm::vec3 EllipsoidGeometry::surface(float u, float v) {
    return glm::vec3{
            m_width / 2.0f * std::sin(u) * std::cos(v),
            m_height / 2.0f * std::sin(v),
            m_depth / 2.0f * std::cos(u) * std::cos(v),
    };
}
