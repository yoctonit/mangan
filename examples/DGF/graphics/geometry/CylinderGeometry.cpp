#include "CylinderGeometry.h"

CylinderGeometry::CylinderGeometry()
        : CylinderGeometry(1.0f, 1.0f, 32, 4, true) {}

CylinderGeometry::CylinderGeometry(
        float radius, float height,
        int radialSegments, int heightSegments, bool closed
) : CylindricalGeometry(
        radius, radius, height,
        radialSegments, heightSegments, closed, closed
) {}
