#include <cmath>
#include <glm/vec3.hpp>
#include "PolygonGeometry.h"

PolygonGeometry::PolygonGeometry()
        : PolygonGeometry(3, 1.0f) {}


PolygonGeometry::PolygonGeometry(int sides, float radius) {
    std::vector<glm::vec3> positionList;
    std::vector<glm::vec3> colorList;
    std::vector<glm::vec2> uvList;

    glm::vec3 positionCenter(0.0f, 0.0f, 0.0f);
    glm::vec3 C1(1.0f, 1.0f, 1.0f);
    glm::vec3 C2(1.0f, 0.0f, 0.0f);
    glm::vec3 C3(0.0f, 0.0f, 1.0f);
    glm::vec2 uvCenter(0.5f, 0.5f);

    float A = 2.0f * static_cast<float>(M_PI) / static_cast<float>(sides);

    for (int n = 0; n < sides; n++) {
        positionList.push_back(positionCenter);
        positionList.emplace_back(
                radius * std::cos(static_cast<float>(n) * A),
                radius * std::sin(static_cast<float>(n) * A),
                0.0f);
        positionList.emplace_back(
                radius * std::cos(static_cast<float>(n + 1) * A),
                radius * std::sin(static_cast<float>(n + 1) * A),
                0.0f);

        colorList.push_back(C1);
        colorList.push_back(C2);
        colorList.push_back(C3);

        uvList.push_back(uvCenter);
        uvList.emplace_back(
                std::cos(static_cast<float>(n) * A) * 0.5f + 0.5f,
                std::sin(static_cast<float>(n) * A) * 0.5f + 0.5f);
        uvList.emplace_back(
                std::cos(static_cast<float>(n + 1) * A) * 0.5f + 0.5f,
                std::sin(static_cast<float>(n + 1) * A) * 0.5f + 0.5f);
    }

    auto positionData = Geometry::flatten(positionList);
    auto colorData = Geometry::flatten(colorList);
    auto uvData = Geometry::flatten(uvList);

    addAttribute("vertexPosition", Attribute::Type::Vec3, positionData);
    addAttribute("vertexColor", Attribute::Type::Vec3, colorData);
    addAttribute("vertexUV", Attribute::Type::Vec2, uvData);

    m_vertexCount = sides * 3;
}
