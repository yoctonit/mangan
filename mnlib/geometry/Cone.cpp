#include "Cone.h"

namespace Mn {

    Cone::Cone(
            float radius, float height,
            int radialSegments, int heightSegments,
            bool closed
    ) : Cylindrical(
            0.0f, radius, height,
            radialSegments, heightSegments, false,
            closed
    ) {}

}
