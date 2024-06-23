#include "SurfaceGeometry.h"

SurfaceGeometry::SurfaceGeometry(
        float uStart, float uEnd, int uResolution,
        float vStart, float vEnd, int vResolution
) :
        m_uStart{uStart}, m_uEnd{uEnd}, m_uResolution{uResolution},
        m_vStart{vStart}, m_vEnd{vEnd}, m_vResolution{vResolution} {}

void SurfaceGeometry::calculateSurface() {
    auto positions = getPoints(
            m_uStart, m_uEnd, m_uResolution,
            m_vStart, m_vEnd, m_vResolution
    );

    std::vector<glm::vec3> quadColors{
            glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f)
    };

    std::vector<glm::vec3> positionList;
    std::vector<glm::vec3> colorList;

    for (int uIndex = 0; uIndex < m_uResolution; uIndex++) {
        for (int vIndex = 0; vIndex < m_vResolution; vIndex++) {
            // position coordinates
            glm::vec3 pA = positions[uIndex + 0][vIndex + 0];
            glm::vec3 pB = positions[uIndex + 1][vIndex + 0];
            glm::vec3 pD = positions[uIndex + 0][vIndex + 1];
            glm::vec3 pC = positions[uIndex + 1][vIndex + 1];
            // positionList.addAll(Arrays.asList(pA, pB, pC, pA, pC, pD));
            positionList.push_back(pA);
            positionList.push_back(pB);
            positionList.push_back(pC);
            positionList.push_back(pA);
            positionList.push_back(pC);
            positionList.push_back(pD);

            // colorList.addAll(quadColors);
            colorList.insert(std::end(colorList), std::begin(quadColors), std::end(quadColors));
        }
    }

    // float [] positionData = Vector.flattenList(positionList);
    auto positionData = Geometry::flatten(positionList);
    // float [] colorData = Vector.flattenList(colorList);
    auto colorData = Geometry::flatten(colorList);

    addAttribute("vertexPosition", Attribute::Type::Vec3, positionData);
    addAttribute("vertexColor", Attribute::Type::Vec3, colorData);
    m_vertexCount = m_uResolution * m_vResolution * 6;
}

std::vector<std::vector<glm::vec3>> SurfaceGeometry::getPoints(
        float uStart, float uEnd, int uResolution,
        float vStart, float vEnd, int vResolution) {

    // points = new glm::vec3[uResolution + 1][vResolution + 1];
    std::vector<std::vector<glm::vec3>> points(uResolution + 1);
    for (auto &row: points) {
        row.reserve(vResolution + 1);
    }

    float deltaU = (uEnd - uStart) / static_cast<float>(uResolution);
    float deltaV = (vEnd - vStart) / static_cast<float>(vResolution);

    for (int uIndex = 0; uIndex < uResolution + 1; uIndex++) {
        for (int vIndex = 0; vIndex < vResolution + 1; vIndex++) {
            float u = uStart + static_cast<float>(uIndex) * deltaU;
            float v = vStart + static_cast<float>(vIndex) * deltaV;
            points[uIndex][vIndex] = surface(u, v);
        }
    }

    return points;
}
