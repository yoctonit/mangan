#include "Sphere.h"

namespace Mn {

    Sphere::Sphere(float radius, int radiusSegments, int heightSegments)
            : Ellipsoid(
            2.0f * radius, 2.0f * radius, 2.0f * radius,
            radiusSegments, heightSegments
    ) {}
}