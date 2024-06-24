#include "PyramidGeometry.h"

PyramidGeometry::PyramidGeometry()
        : PyramidGeometry(1.0f, 1.0f, 4, 4, true) {}

PyramidGeometry::PyramidGeometry(
        float radius, float height,
        int sides, int heightSegments, bool closed
) : CylindricalGeometry(
        0.0f, radius, height,
        sides, heightSegments, false, closed
) {}
