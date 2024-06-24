#include "PrismGeometry.h"

PrismGeometry::PrismGeometry()
        : PrismGeometry(1.0f, 1.0f, 6, 4, true) {}

PrismGeometry::PrismGeometry(
        float radius, float height,
        int sides, int heightSegments, bool closed
) : CylindricalGeometry(
        radius, radius, height,
        sides, heightSegments, closed, closed
) {}
