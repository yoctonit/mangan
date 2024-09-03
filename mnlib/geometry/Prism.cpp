#include "Prism.h"

namespace Mn {

    Prism::Prism(
            float radius, float height,
            int sides, int heightSegments, bool closed
    ) : Cylindrical(
            radius, radius, height,
            sides, heightSegments,
            closed, closed
    ) {}

}