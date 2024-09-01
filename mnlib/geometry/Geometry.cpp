#include "Geometry.h"

namespace Mn {

    std::vector<float> Geometry::Data(Type type) const {
        std::vector<float> data;

        switch (type) {
            case Type::Positions:
                for (const auto &vertex: mVertices) {
                    data.push_back(vertex.x);
                    data.push_back(vertex.y);
                    data.push_back(vertex.z);
                }
                break;
            case Type::Normals:
                for (const auto &normal: mNormals) {
                    data.push_back(normal.x);
                    data.push_back(normal.y);
                    data.push_back(normal.z);
                }
                break;
            case Type::TexCoords:
                for (const auto &texCoord: mTexCoords) {
                    data.push_back(texCoord.x);
                    data.push_back(texCoord.y);
                }
                break;
            case Type::PositionsAndNormals:
                for (int i = 0; i < mVertices.size(); i++) {
                    data.push_back(mVertices[i].x);
                    data.push_back(mVertices[i].y);
                    data.push_back(mVertices[i].z);

                    data.push_back(mNormals[i].x);
                    data.push_back(mNormals[i].y);
                    data.push_back(mNormals[i].z);
                }
                break;
            case Type::PositionsAndTexCoords:
                for (int i = 0; i < mVertices.size(); i++) {
                    data.push_back(mVertices[i].x);
                    data.push_back(mVertices[i].y);
                    data.push_back(mVertices[i].z);

                    data.push_back(mTexCoords[i].x);
                    data.push_back(mTexCoords[i].y);
                }
                break;
            case Type::NormalsAndTexCoords:
                for (int i = 0; i < mNormals.size(); i++) {
                    data.push_back(mNormals[i].x);
                    data.push_back(mNormals[i].y);
                    data.push_back(mNormals[i].z);

                    data.push_back(mTexCoords[i].x);
                    data.push_back(mTexCoords[i].y);
                }
                break;
            case Type::PositionsNormalsAndTexCoords:
                for (int i = 0; i < mVertices.size(); i++) {
                    data.push_back(mVertices[i].x);
                    data.push_back(mVertices[i].y);
                    data.push_back(mVertices[i].z);

                    data.push_back(mNormals[i].x);
                    data.push_back(mNormals[i].y);
                    data.push_back(mNormals[i].z);

                    data.push_back(mTexCoords[i].x);
                    data.push_back(mTexCoords[i].y);
                }
                break;
        }

        return data;
    }

    int Geometry::VertexCount() const {
        return mVertexCount;
    };

//    void Geometry::VertexCount(int vertexCount) {
//        mVertexCount = vertexCount;
//    }

    void Geometry::ApplyMatrix(const glm::mat4x4 &matrix) {
        // update vertex position data
        for (auto &vertex: mVertices) {
            // add homogeneous fourth coordinate
            glm::vec4 tmp(vertex, 1.0f);
            // multiply by matrix
            glm::vec4 newPos = matrix * tmp;
            vertex = glm::vec3(newPos);
        }

        // update vertex normal data
        // 1. extract the rotation sub matrix
        auto rotationMatrix = glm::mat3(matrix);
        // 2. recalculate normals
        for (auto &normal: mNormals) {
            glm::vec3 newNormal = rotationMatrix * normal;
            normal = newNormal;
        }
    }

    void Geometry::Merge(const Geometry &other) {
        for (const auto &vertex: other.mVertices) {
            mVertices.push_back(vertex);
        }

        for (const auto &normal: other.mNormals) {
            mNormals.push_back(normal);
        }

        for (const auto &texCoord: other.mTexCoords) {
            mTexCoords.push_back(texCoord);
        }

        mVertexCount += other.mVertexCount;
    }

    glm::vec3 Geometry::CalculateNormal(glm::vec3 P0, glm::vec3 P1, glm::vec3 P2) {
        glm::vec3 v1 = P1 - P0;
        glm::vec3 v2 = P2 - P0;
        glm::vec3 normal = glm::cross(v1, v2);
        return glm::normalize(normal);
    }

}
