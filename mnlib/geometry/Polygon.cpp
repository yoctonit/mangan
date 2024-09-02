#include <cmath>
#include "Polygon.h"

namespace Mn {

    Polygon::Polygon(int sides, float radius) {
        Create(sides, radius);
    }

    void Polygon::Create(int sides, float radius) {

        glm::vec3 positionCenter(0.0f, 0.0f, 0.0f);
        glm::vec3 normalVector(0.0f, 0.0f, 1.0f);
        glm::vec2 uvCenter(0.5f, 0.5f);

        float A = 2.0f * static_cast<float>(M_PI) / static_cast<float>(sides);

        for (int n = 0; n < sides; n++) {
            mVertices.push_back(positionCenter);
            mVertices.emplace_back(
                    radius * std::cos(static_cast<float>(n) * A),
                    radius * std::sin(static_cast<float>(n) * A),
                    0.0f);
            mVertices.emplace_back(
                    radius * std::cos(static_cast<float>(n + 1) * A),
                    radius * std::sin(static_cast<float>(n + 1) * A),
                    0.0f);

            mNormals.push_back(normalVector);
            mNormals.push_back(normalVector);
            mNormals.push_back(normalVector);

            mTexCoords.push_back(uvCenter);
            mTexCoords.emplace_back(
                    std::cos(static_cast<float>(n) * A) * 0.5f + 0.5f,
                    std::sin(static_cast<float>(n) * A) * 0.5f + 0.5f);
            mTexCoords.emplace_back(
                    std::cos(static_cast<float>(n + 1) * A) * 0.5f + 0.5f,
                    std::sin(static_cast<float>(n + 1) * A) * 0.5f + 0.5f);
        }

        mVertexCount = sides * 3;
    }

}