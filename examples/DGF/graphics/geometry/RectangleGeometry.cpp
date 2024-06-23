#include <glm/vec3.hpp>
#include "RectangleGeometry.h"

RectangleGeometry::RectangleGeometry() : RectangleGeometry(1.0f, 1.0f) {}


RectangleGeometry::RectangleGeometry(float width, float height) {
    glm::vec3 P0(-width / 2.0f, -height / 2.0f, 0.0f);
    glm::vec3 P1(width / 2.0f, -height / 2.0f, 0.0f);
    glm::vec3 P2(-width / 2.0f, height / 2.0f, 0.0f);
    glm::vec3 P3(width / 2.0f, height / 2.0f, 0.0f);

    glm::vec3 C0(1.0f, 1.0f, 1.0f);
    glm::vec3 C1(1.0f, 0.0f, 0.0f);
    glm::vec3 C2(0.0f, 1.0f, 0.0f);
    glm::vec3 C3(0.0f, 0.0f, 1.0f);

    std::vector<glm::vec3> positionList{P0, P1, P3, P0, P3, P2};
    std::vector<GLfloat> positionData = Geometry::flatten(positionList);

    std::vector<glm::vec3> colorList{C0, C1, C3, C0, C3, C2};
    std::vector<GLfloat> colorData = Geometry::flatten(colorList);

    addAttribute("vertexPosition", Attribute::Type::Vec3, positionData);
    addAttribute("vertexColor", Attribute::Type::Vec3, colorData);
    m_vertexCount = 6;
}
