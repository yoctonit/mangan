#include <cmath>
#include "Ellipsoid.h"

namespace Mn {

    Ellipsoid::Ellipsoid(
            float width, float height, float depth,
            int radiusSegments, int heightSegments
    ) : Surface(
            0.0f, 2.0f * M_PI, radiusSegments,
            -M_PI / 2.0f, M_PI / 2.0f, heightSegments
    ) {
        CalculateSurface(Equation(width, height, depth));
    }

    Ellipsoid::Equation::Equation(float width, float height, float depth)
            : mWidth{width}, mHeight{height}, mDepth{depth} {}

    glm::vec3 Ellipsoid::Equation::operator()(float u, float v) const {
        return glm::vec3{
                mWidth / 2.0f * std::sin(u) * std::cos(v),
                mHeight / 2.0f * std::sin(v),
                mDepth / 2.0f * std::cos(u) * std::cos(v),
        };
    }

}