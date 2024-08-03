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

    auto uvs = getUVs(
            m_uStart, m_uEnd, m_uResolution,
            m_vStart, m_vEnd, m_vResolution
    );

    std::vector<glm::vec3> quadColors{
            glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f)
    };

    auto vertexNormals = getNormals(
            m_uStart, m_uEnd, m_uResolution,
            m_vStart, m_vEnd, m_vResolution);

    std::vector<glm::vec3> positionList;
    std::vector<glm::vec3> colorList;
    std::vector<glm::vec2> uvList;
    std::vector<glm::vec3> vertexNormalList;
    std::vector<glm::vec3> faceNormalList;

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

            // uv coordinates
            glm::vec2 uvA = uvs[uIndex + 0][vIndex + 0];
            glm::vec2 uvB = uvs[uIndex + 1][vIndex + 0];
            glm::vec2 uvD = uvs[uIndex + 0][vIndex + 1];
            glm::vec2 uvC = uvs[uIndex + 1][vIndex + 1];
            uvList.push_back(uvA);
            uvList.push_back(uvB);
            uvList.push_back(uvC);
            uvList.push_back(uvA);
            uvList.push_back(uvC);
            uvList.push_back(uvD);

            // vertex normal vectors
            glm::vec3 nA = vertexNormals[uIndex + 0][vIndex + 0];
            glm::vec3 nB = vertexNormals[uIndex + 1][vIndex + 0];
            glm::vec3 nD = vertexNormals[uIndex + 0][vIndex + 1];
            glm::vec3 nC = vertexNormals[uIndex + 1][vIndex + 1];
            // vertexNormalList.addAll( Arrays.asList(nA,nB,nC, nA,nC,nD) );
            vertexNormalList.push_back(nA);
            vertexNormalList.push_back(nB);
            vertexNormalList.push_back(nC);
            vertexNormalList.push_back(nA);
            vertexNormalList.push_back(nC);
            vertexNormalList.push_back(nD);

            // face normal vectors
            glm::vec3 fn0 = Geometry::calcNormal(pA, pB, pC);
            glm::vec3 fn1 = Geometry::calcNormal(pA, pC, pD);
            // faceNormalList.addAll( Arrays.asList(fn0,fn0,fn0, fn1,fn1,fn1) );
            faceNormalList.push_back(fn0);
            faceNormalList.push_back(fn0);
            faceNormalList.push_back(fn0);
            faceNormalList.push_back(fn1);
            faceNormalList.push_back(fn1);
            faceNormalList.push_back(fn1);
        }
    }

    auto positionData = Geometry::flatten(positionList);
    auto colorData = Geometry::flatten(colorList);
    auto uvData = Geometry::flatten(uvList);
    auto vertexNormalData = Geometry::flatten(vertexNormalList);
    auto faceNormalData = Geometry::flatten(faceNormalList);

    addAttribute("vertexPosition", Attribute::Type::Vec3, positionData);
    addAttribute("vertexColor", Attribute::Type::Vec3, colorData);
    addAttribute("vertexUV", Attribute::Type::Vec2, uvData);
    addAttribute("vertexNormal", Attribute::Type::Vec3, vertexNormalData);
    addAttribute("faceNormal", Attribute::Type::Vec3, faceNormalData);

    m_vertexCount = m_uResolution * m_vResolution * 6;
}

std::vector<std::vector<glm::vec3>> SurfaceGeometry::getPoints(
        float uStart, float uEnd, int uResolution,
        float vStart, float vEnd, int vResolution) {

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

std::vector<std::vector<glm::vec2>> SurfaceGeometry::getUVs(
        float uStart, float uEnd, int uResolution,
        float vStart, float vEnd, int vResolution) {

    std::vector<std::vector<glm::vec2>> uvs(uResolution + 1);
    for (auto &row: uvs) {
        row.reserve(vResolution + 1);
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

std::vector<std::vector<glm::vec3>> SurfaceGeometry::getNormals(
        float uStart, float uEnd, int uResolution,
        float vStart, float vEnd, int vResolution
) {
    std::vector<std::vector<glm::vec3>> normals(uResolution + 1);
    for (auto &row: normals) {
        row.reserve(vResolution + 1);
    }

    float deltaU = (uEnd - uStart) / static_cast<float>(uResolution);
    float deltaV = (vEnd - vStart) / static_cast<float>(vResolution);

    for (int uIndex = 0; uIndex < uResolution + 1; uIndex++) {
        for (int vIndex = 0; vIndex < vResolution + 1; vIndex++) {
            float u = uStart + static_cast<float>(uIndex) * deltaU;
            float v = vStart + static_cast<float>(vIndex) * deltaV;
            float h = 0.0001;
            glm::vec3 P0 = surface(u, v);
            glm::vec3 P1 = surface(u + h, v);
            glm::vec3 P2 = surface(u, v + h);
            normals[uIndex][vIndex] = Geometry::calcNormal(P0, P1, P2);
        }
    }

    return normals;
}
