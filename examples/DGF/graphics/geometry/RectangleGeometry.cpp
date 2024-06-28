#include <glm/vec3.hpp>
#include "RectangleGeometry.h"

RectangleGeometry::RectangleGeometry()
        : RectangleGeometry(1.0f, 1.0f) {}


RectangleGeometry::RectangleGeometry(float width, float height)
        : RectangleGeometry(
        width, height,
        glm::vec2(0.0f, 0.0f),
        glm::vec2(0.5f, 0.5f)
) {}

RectangleGeometry::RectangleGeometry(float width, float height, glm::vec2 position, glm::vec2 alignment) {
    float x = position.x;
    float y = position.y;
    float a = alignment.x;
    float b = alignment.y;

    glm::vec3 P0(x + (-a) * width, y + (-b) * height, 0.0f);
    glm::vec3 P1(x + (1.0f - a) * width, y + (-b) * height, 0.0f);
    glm::vec3 P2(x + (-a) * width, y + (1.0f - b) * height, 0.0f);
    glm::vec3 P3(x + (1.0f - a) * width, y + (1.0f - b) * height, 0.0f);

    glm::vec3 C0(1.0f, 1.0f, 1.0f);
    glm::vec3 C1(1.0f, 0.0f, 0.0f);
    glm::vec3 C2(0.0f, 1.0f, 0.0f);
    glm::vec3 C3(0.0f, 0.0f, 1.0f);

    // texture coordinates
    glm::vec2 T0(0.0f, 0.0f);
    glm::vec2 T1(1.0f, 0.0f);
    glm::vec2 T2(0.0f, 1.0f);
    glm::vec2 T3(1.0f, 1.0f);

    std::vector<glm::vec3> positionList{P0, P1, P3, P0, P3, P2};
    std::vector<GLfloat> positionData = Geometry::flatten(positionList);

    std::vector<glm::vec3> colorList{C0, C1, C3, C0, C3, C2};
    std::vector<GLfloat> colorData = Geometry::flatten(colorList);

    std::vector<glm::vec2> uvList{T0, T1, T3, T0, T3, T2};
    std::vector<GLfloat> uvData = Geometry::flatten(uvList);

    addAttribute("vertexPosition", Attribute::Type::Vec3, positionData);
    addAttribute("vertexColor", Attribute::Type::Vec3, colorData);
    addAttribute("vertexUV", Attribute::Type::Vec2, uvData);

    m_vertexCount = 6;
}
