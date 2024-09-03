#include "Pyramid.h"

namespace Mn {

    Pyramid::Pyramid(
            float radius, float height,
            int sides, int heightSegments,
            bool closed
    ) : Cylindrical(
            0.0f, radius, height,
            sides, heightSegments,
            false, closed
    ) {}

}