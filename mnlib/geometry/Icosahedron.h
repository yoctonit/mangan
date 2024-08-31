#ifndef INCLUDED_MN_GEOMETRY_ICOSAHEDRON_H
#define INCLUDED_MN_GEOMETRY_ICOSAHEDRON_H

#include <vector>
#include <cmath>
#include <glm/vec3.hpp>

namespace Mn {

    class Icosahedron {
    public:
        void Create(float radius = 1.0f, int levelOfRecursion = 3);

        [[nodiscard]] const std::vector<glm::vec3> &Vertices() const;

        [[nodiscard]] const std::vector<glm::vec3> &Normals() const;

        [[nodiscard]] int numberOfVertices() const;

    private:
        float mRadius{};
        int mLevelOfRecursion{};

        std::vector<glm::vec3> mVertices;
        std::vector<glm::vec3> mNormals;

        void Subdivide(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, int lor);
    };

}

#endif //INCLUDED_MN_GEOMETRY_ICOSAHEDRON_H
