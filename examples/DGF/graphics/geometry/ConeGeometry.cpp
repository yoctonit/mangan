#include "ConeGeometry.h"

ConeGeometry::ConeGeometry()
        : ConeGeometry(1.0f, 1.0f, 32, 4, true) {}

ConeGeometry::ConeGeometry(
        float radius, float height,
        int radialSegments, int heightSegments, bool closed
) : CylindricalGeometry(
        0.0f, radius, height,
        radialSegments, heightSegments, false, closed
) {}
