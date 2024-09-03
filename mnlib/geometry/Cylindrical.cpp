#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

#include "Cylindrical.h"
#include "Polygon.h"

namespace Mn {

    Cylindrical::Cylindrical(
            float radiusTop, float radiusBottom, float height,
            int radialSegments, int heightSegments,
            bool closedTop, bool closedBottom
    ) : Surface(
            0.0f, 2.0f * M_PI, radialSegments,
            0.0f, 1.0f, heightSegments
    ) {

        CalculateSurface(Equation(radiusTop, radiusBottom, height));

        auto PI = static_cast<float>(M_PI);
        if (closedTop) {
            Polygon topGeometry(radialSegments, radiusTop);

            auto transform = glm::mat4(1.0f);
            transform = glm::translate(transform, glm::vec3(0.0f, height / 2.0f, 0.0f));
            transform = glm::rotate(transform, -PI / 2.0f, glm::vec3(0.0f, 1.0f, 0.0f));
            transform = glm::rotate(transform, -PI / 2.0f, glm::vec3(1.0f, 0.0f, 0.0f));

            topGeometry.ApplyMatrix(transform);
            Merge(topGeometry);
        }

        if (closedBottom) {
            Polygon bottomGeometry(radialSegments, radiusBottom);

            auto transform = glm::mat4(1.0f);
            transform = glm::translate(transform, glm::vec3(0.0f, -height / 2.0f, 0.0f));
            transform = glm::rotate(transform, -PI / 2.0f, glm::vec3(0.0f, 1.0f, 0.0f));
            transform = glm::rotate(transform, PI / 2.0f, glm::vec3(1.0f, 0.0f, 0.0f));

            bottomGeometry.ApplyMatrix(transform);
            Merge(bottomGeometry);
        }
    }

    Cylindrical::Equation::Equation(float radiusTop, float radiusBottom, float height)
            : mRadiusTop{radiusTop}, mRadiusBottom{radiusBottom}, mHeight{height} {}

    glm::vec3 Cylindrical::Equation::operator()(float u, float v) const {
        return glm::vec3{
                (v * mRadiusTop + (1 - v) * mRadiusBottom) * std::sin(u),
                mHeight * (v - 0.5f),
                (v * mRadiusTop + (1 - v) * mRadiusBottom) * std::cos(u),
        };
    }
}
