#include "Cylinder.h"

namespace Mn {

    Cylinder::Cylinder(
            float radius, float height,
            int radialSegments, int heightSegments, bool closed
    ) : Cylindrical(
            radius, radius, height,
            radialSegments, heightSegments,
            closed, closed
    ) {}

}
