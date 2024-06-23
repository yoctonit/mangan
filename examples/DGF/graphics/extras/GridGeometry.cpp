#include <glm/vec3.hpp>
#include "GridGeometry.h"

GridGeometry::GridGeometry() :
        GridGeometry(
                10.0f, 10.0f,
                glm::vec3(0.5f, 0.5f, 0.5f),
                glm::vec3(0.8f, 0.8f, 0.8f)
        ) {}

GridGeometry::GridGeometry(
        float size, int divisions,
        glm::vec3 gridColor, glm::vec3 centerColor
) {

    float deltaSize = size / static_cast<float>(divisions);

    std::vector<float> values;
    values.reserve(divisions + 1);
    for (int n = 0; n < divisions + 1; n++)
        values.push_back(-size / 2.0f + static_cast<float>(n) * deltaSize);

    std::vector<glm::vec3> positionList;
    std::vector<glm::vec3> colorList;

    // add vertical lines
    for (auto x: values) {
        positionList.emplace_back(x, -size / 2.0f, 0.0f);
        positionList.emplace_back(x, size / 2.0f, 0.0f);
        if (x == 0) {
            colorList.push_back(centerColor);
            colorList.push_back(centerColor);
        } else {
            colorList.push_back(gridColor);
            colorList.push_back(gridColor);
        }
    }

    // add horizontal lines
    for (auto y: values) {
        positionList.emplace_back(-size / 2.0f, y, 0.0f);
        positionList.emplace_back(size / 2.0f, y, 0.0f);
        if (y == 0) {
            colorList.push_back(centerColor);
            colorList.push_back(centerColor);
        } else {
            colorList.push_back(gridColor);
            colorList.push_back(gridColor);
        }
    }

    auto positionData = Geometry::flatten(positionList);
    auto colorData = Geometry::flatten(colorList);

    addAttribute("vertexPosition", Attribute::Type::Vec3, positionData);
    addAttribute("vertexColor", Attribute::Type::Vec3, colorData);
    m_vertexCount = static_cast<int>(positionList.size());
}
