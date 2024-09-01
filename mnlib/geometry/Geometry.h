#ifndef INCLUDED_MN_GEOMETRY_GEOMETRY_H
#define INCLUDED_MN_GEOMETRY_GEOMETRY_H

#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace Mn {

    class Geometry {
    public:
        enum class Type {
            Positions, Normals, TexCoords,
            PositionsAndNormals, PositionsAndTexCoords, NormalsAndTexCoords,
            PositionsNormalsAndTexCoords
        };

        [[nodiscard]] std::vector<float> Data(Type type) const;

        [[nodiscard]] int VertexCount() const;

//        void VertexCount(int vertexCount);

//        [[nodiscard]] const std::vector<glm::vec3> &Vertices() const;

//        [[nodiscard]] const std::vector<glm::vec3> &Normals() const;

//        [[nodiscard]] const std::vector<glm::vec2> &TexCoords() const;

        // transform vertex position and normal data using a matrix
        void ApplyMatrix(const glm::mat4x4 &matrix);

        // merge data of other geometry into this object
        void Merge(const Geometry &other);

    protected:
        int mVertexCount{};
        std::vector<glm::vec3> mVertices;
        std::vector<glm::vec3> mNormals;
        std::vector<glm::vec2> mTexCoords;

        static glm::vec3 CalculateNormal(glm::vec3 P0, glm::vec3 P1, glm::vec3 P2);
    };

}

#endif //INCLUDED_MN_GEOMETRY_GEOMETRY_H
