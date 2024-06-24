#include "PlaneGeometry.h"

PlaneGeometry::PlaneGeometry()
        : PlaneGeometry(1.0f, 1.0f, 8, 8) {}


PlaneGeometry::PlaneGeometry(
        float width, float height,
        int widthSegments, int heightSegments
) : SurfaceGeometry(
        -width / 2.0f, width / 2.0f, widthSegments,
        -height / 2.0f, height / 2.0f, heightSegments
) {
    calculateSurface();
}

glm::vec3 PlaneGeometry::surface(float u, float v) {
    return glm::vec3{u, v, 0.0f};
}
