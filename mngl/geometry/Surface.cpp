#include "Surface.h"

namespace Mn {
    Surface::Surface(
            float uStart, float uEnd, int uResolution,
            float vStart, float vEnd, int vResolution
    ) :
            m_uStart{uStart}, m_uEnd{uEnd}, m_uResolution{uResolution},
            m_vStart{vStart}, m_vEnd{vEnd}, m_vResolution{vResolution} {}

    void Surface::CalculateSurface(const SurfaceEquation &surfaceEquation) {
        auto positions = getPoints(
                m_uStart, m_uEnd, m_uResolution,
                m_vStart, m_vEnd, m_vResolution,
                surfaceEquation
        );

        auto vertexNormals = getNormals(
                m_uStart, m_uEnd, m_uResolution,
                m_vStart, m_vEnd, m_vResolution,
                surfaceEquation
        );

        auto uvs = getUVs(m_uResolution, m_vResolution);

        for (int uIndex = 0; uIndex < m_uResolution; uIndex++) {
            for (int vIndex = 0; vIndex < m_vResolution; vIndex++) {
                // position coordinates
                glm::vec3 pA = positions[uIndex + 0][vIndex + 0];
                glm::vec3 pB = positions[uIndex + 1][vIndex + 0];
                glm::vec3 pC = positions[uIndex + 1][vIndex + 1];
                glm::vec3 pD = positions[uIndex + 0][vIndex + 1];

                mVertices.push_back(pA);
                mVertices.push_back(pB);
                mVertices.push_back(pC);
                mVertices.push_back(pA);
                mVertices.push_back(pC);
                mVertices.push_back(pD);

                // vertex normal vectors
                glm::vec3 nA = vertexNormals[uIndex + 0][vIndex + 0];
                glm::vec3 nB = vertexNormals[uIndex + 1][vIndex + 0];
                glm::vec3 nC = vertexNormals[uIndex + 1][vIndex + 1];
                glm::vec3 nD = vertexNormals[uIndex + 0][vIndex + 1];

                mNormals.push_back(nA);
                mNormals.push_back(nB);
                mNormals.push_back(nC);
                mNormals.push_back(nA);
                mNormals.push_back(nC);
                mNormals.push_back(nD);

                // uv coordinates
                glm::vec2 uvA = uvs[uIndex + 0][vIndex + 0];
                glm::vec2 uvB = uvs[uIndex + 1][vIndex + 0];
                glm::vec2 uvC = uvs[uIndex + 1][vIndex + 1];
                glm::vec2 uvD = uvs[uIndex + 0][vIndex + 1];

                mTexCoords.push_back(uvA);
                mTexCoords.push_back(uvB);
                mTexCoords.push_back(uvC);
                mTexCoords.push_back(uvA);
                mTexCoords.push_back(uvC);
                mTexCoords.push_back(uvD);
            }
        }

        // two triangles per quad
        mVertexCount = m_uResolution * m_vResolution * 6;
    }

    std::vector<std::vector<glm::vec3>> Surface::getPoints(
            float uStart, float uEnd, int uResolution,
            float vStart, float vEnd, int vResolution,
            const SurfaceEquation &surfaceEquation
    ) {
        std::vector<std::vector<glm::vec3>> points(uResolution + 1);
        for (auto &col: points) {
            col.reserve(vResolution + 1);
        }

        float deltaU = (uEnd - uStart) / static_cast<float>(uResolution);
        float deltaV = (vEnd - vStart) / static_cast<float>(vResolution);

        for (int uIndex = 0; uIndex < uResolution + 1; uIndex++) {
            for (int vIndex = 0; vIndex < vResolution + 1; vIndex++) {
                float u = uStart + static_cast<float>(uIndex) * deltaU;
                float v = vStart + static_cast<float>(vIndex) * deltaV;
                points[uIndex][vIndex] = surfaceEquation(u, v);
            }
        }

        return points;
    }

    std::vector<std::vector<glm::vec3>> Surface::getNormals(
            float uStart, float uEnd, int uResolution,
            float vStart, float vEnd, int vResolution,
            const SurfaceEquation &surfaceEquation
    ) {
        std::vector<std::vector<glm::vec3>> normals(uResolution + 1);
        for (auto &col: normals) {
            col.reserve(vResolution + 1);
        }

        float deltaU = (uEnd - uStart) / static_cast<float>(uResolution);
        float deltaV = (vEnd - vStart) / static_cast<float>(vResolution);

        for (int uIndex = 0; uIndex < uResolution + 1; uIndex++) {
            for (int vIndex = 0; vIndex < vResolution + 1; vIndex++) {
                float u = uStart + static_cast<float>(uIndex) * deltaU;
                float v = vStart + static_cast<float>(vIndex) * deltaV;
                float h = 0.0001;
                glm::vec3 P0 = surfaceEquation(u, v);
                glm::vec3 P1 = surfaceEquation(u + h, v);
                glm::vec3 P2 = surfaceEquation(u, v + h);
                normals[uIndex][vIndex] = Geometry::CalculateNormal(P0, P1, P2);
            }
        }

        return normals;
    }

    std::vector<std::vector<glm::vec2>> Surface::getUVs(int uResolution, int vResolution) {

        std::vector<std::vector<glm::vec2>> uvs(uResolution + 1);
        for (auto &col: uvs) {
            col.reserve(vResolution + 1);
        }

        for (int uIndex = 0; uIndex < uResolution + 1; uIndex++) {
            for (int vIndex = 0; vIndex < vResolution + 1; vIndex++) {
                float u = (float) uIndex / static_cast<float>(uResolution);
                float v = (float) vIndex / static_cast<float>(vResolution);
                uvs[uIndex][vIndex] = glm::vec2(u, v);
            }
        }

        return uvs;
    }

}