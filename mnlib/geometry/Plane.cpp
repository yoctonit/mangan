#include "Plane.h"

namespace Mn {
    Plane::Plane(
            float width, float height,
            int widthSegments, int heightSegments
    ) : Surface(
            -width / 2.0f, width / 2.0f, widthSegments,
            -height / 2.0f, height / 2.0f, heightSegments
    ) {
        CalculateSurface();
    }

    glm::vec3 Plane::SurfaceEquation(float u, float v) {
        return glm::vec3{u, v, 0.0f};
    }
}
