#include "SphereGeometry.h"

SphereGeometry::SphereGeometry()
        : SphereGeometry(1.0f, 32, 16) {}

SphereGeometry::SphereGeometry(float radius)
        : SphereGeometry(radius, 32, 16) {}

SphereGeometry::SphereGeometry(float radius, int radiusSegments, int heightSegments)
        : EllipsoidGeometry(
        2.0f * radius, 2.0f * radius, 2.0f * radius,
        radiusSegments, heightSegments
) {
//    calculateSurface();
}
