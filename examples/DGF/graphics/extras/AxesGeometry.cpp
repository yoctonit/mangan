#include <glm/vec3.hpp>
#include "AxesGeometry.h"

AxesGeometry::AxesGeometry() : AxesGeometry(1.0f) {}

AxesGeometry::AxesGeometry(float axisLength) {

    std::vector<glm::vec3> positionList{
            glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(axisLength, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, axisLength, 0.0f),
            glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, axisLength)
    };
    std::vector<float> positionData = Geometry::flatten(positionList);

    std::vector<glm::vec3> colorList{
            glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(1.0f, 0.5f, 0.5f),
            glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.5f, 1.0f, 0.5f),
            glm::vec3(0.0f, 0.0f, 0.5f), glm::vec3(0.5f, 0.5f, 1.0f)
    };
    std::vector<float> colorData = Geometry::flatten(colorList);

    addAttribute("vertexPosition", Attribute::Type::Vec3, positionData);
    addAttribute("vertexColor", Attribute::Type::Vec3, colorData);
    m_vertexCount = 6;
}
