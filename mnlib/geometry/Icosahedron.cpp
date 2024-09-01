#include "Icosahedron.h"
#include <vector>
#include <glm/glm.hpp>

namespace Mn {

    Icosahedron::Icosahedron(float radius, int levelOfRecursion) {
        Create(radius, levelOfRecursion);
    }

    void Icosahedron::Create(float radius, int levelOfRecursion) {
        mRadius = radius;

        const float X = .525731112119133606;
        const float Z = .850650808352039932;

        // 12 vertices of unit icosahedron
        std::vector<glm::vec3> base_vertices{
                glm::vec3(-X, 0.0f, Z), glm::vec3(X, 0.0f, Z), glm::vec3(-X, 0.0f, -Z),
                glm::vec3(X, 0.0f, -Z), glm::vec3(0.0f, Z, X), glm::vec3(0.0f, Z, -X),
                glm::vec3(0.0f, -Z, X), glm::vec3(0.0f, -Z, -X), glm::vec3(Z, X, 0.0f),
                glm::vec3(-Z, X, 0.0f), glm::vec3(Z, -X, 0.0f), glm::vec3(-Z, -X, 0.0f)
        };

        // indices of vertices, grouped by 3
        // that is, every 3 indices mark 1 triangle
        std::vector<int> indices{
                1, 4, 0, 4, 9, 0, 4, 5, 9, 8, 5, 4, 1, 8, 4,
                1, 10, 8, 10, 3, 8, 8, 3, 5, 3, 2, 5, 3, 7, 2,
                3, 10, 7, 10, 6, 7, 6, 11, 7, 6, 0, 11, 6, 1, 0,
                10, 1, 6, 11, 0, 9, 2, 11, 9, 5, 2, 9, 11, 2, 7
        };

        // For each face of icosahedron (20 faces * 3 vertices per face)
        for (int i = 0; i < 60; i += 3) {
            Subdivide(
                    base_vertices[indices[i + 0]],
                    base_vertices[indices[i + 1]],
                    base_vertices[indices[i + 2]],
                    levelOfRecursion
            );
        }

        // 20 faces divided to 4 faces levelOfRecursion times, times 3 vertices
        mVertexCount = 20 * static_cast<int>(std::pow(4, levelOfRecursion)) * 3;
    }

    void Icosahedron::Subdivide(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, int levelOfRecursion) {
        if (levelOfRecursion == 0) {
            mVertices.push_back(mRadius * v1);
            mVertices.push_back(mRadius * v2);
            mVertices.push_back(mRadius * v3);

            mNormals.push_back(v1);
            mNormals.push_back(v2);
            mNormals.push_back(v3);

            return;
        }

        glm::vec3 v12 = glm::normalize(0.5f * (v1 + v2));
        glm::vec3 v23 = glm::normalize(0.5f * (v2 + v3));
        glm::vec3 v31 = glm::normalize(0.5f * (v3 + v1));

        Subdivide(v1, v12, v31, levelOfRecursion - 1);
        Subdivide(v2, v23, v12, levelOfRecursion - 1);
        Subdivide(v3, v31, v23, levelOfRecursion - 1);
        Subdivide(v12, v23, v31, levelOfRecursion - 1);
    }

}
