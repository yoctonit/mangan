#include "Plane.h"

namespace Mn {
    Plane::Plane(
            float width, float height,
            int widthSegments, int heightSegments
    ) : Surface(
            -width / 2.0f, width / 2.0f, widthSegments,
            -height / 2.0f, height / 2.0f, heightSegments
    ) {
        CalculateSurface(Equation());
    }

    glm::vec3 Plane::Equation::operator()(float u, float v) const {
        return glm::vec3{u, v, 0.0f};
    }
}
