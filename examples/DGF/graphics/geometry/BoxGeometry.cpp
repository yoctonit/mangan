#include <glm/vec3.hpp>
#include "BoxGeometry.h"

BoxGeometry::BoxGeometry() : BoxGeometry(1.0f, 1.0f, 1.0f) {}

BoxGeometry::BoxGeometry(float width, float height, float depth) {
    // corners of a cube
    glm::vec3 P0(-width / 2.0f, -height / 2.0f, -depth / 2.0f);
    glm::vec3 P1(width / 2, -height / 2, -depth / 2.0f);
    glm::vec3 P2(-width / 2, height / 2, -depth / 2.0f);
    glm::vec3 P3(width / 2, height / 2, -depth / 2.0f);
    glm::vec3 P4(-width / 2, -height / 2, depth / 2.0f);
    glm::vec3 P5(width / 2, -height / 2, depth / 2.0f);
    glm::vec3 P6(-width / 2, height / 2, depth / 2.0f);
    glm::vec3 P7(width / 2, height / 2, depth / 2.0f);

    // colors for faces in order: x+, x-, y+, y-, z+, z-
    glm::vec3 C1(1.0f, 0.5f, 0.5f);
    glm::vec3 C2(0.5f, 0.0f, 0.0f);
    glm::vec3 C3(0.5f, 1.0f, 0.5f);
    glm::vec3 C4(0.0f, 0.5f, 0.0f);
    glm::vec3 C5(0.5f, 0.5f, 1.0f);
    glm::vec3 C6(0.0f, 0.0f, 0.5f);

    // texture coordinates
    glm::vec2 T0(0.0f, 0.0f);
    glm::vec2 T1(1.0f, 0.0f);
    glm::vec2 T2(0.0f, 1.0f);
    glm::vec2 T3(1.0f, 1.0f);

    // normal vectors for x+, x-, y+, y-, z+, z-
    glm::vec3 N1(1.0f, 0.0f, 0.0f);
    glm::vec3 N2(-1.0f, 0.0f, 0.0f);
    glm::vec3 N3(0.0f, 1.0f, 0.0f);
    glm::vec3 N4(0.0f, -1.0f, 0.0f);
    glm::vec3 N5(0.0f, 0.0f, 1.0f);
    glm::vec3 N6(0.0f, 0.0f, -1.0f);

    std::vector<glm::vec3> positionList{
            P5, P1, P3, P5, P3, P7, P0, P4, P6, P0, P6, P2,
            P6, P7, P3, P6, P3, P2, P0, P1, P5, P0, P5, P4,
            P4, P5, P7, P4, P7, P6, P1, P0, P2, P1, P2, P3
    };
    std::vector<float> positionData = Geometry::flatten(positionList);

    std::vector<glm::vec3> colorList{
            C1, C1, C1, C1, C1, C1, C2, C2, C2, C2, C2, C2,
            C3, C3, C3, C3, C3, C3, C4, C4, C4, C4, C4, C4,
            C5, C5, C5, C5, C5, C5, C6, C6, C6, C6, C6, C6
    };
    std::vector<float> colorData = Geometry::flatten(colorList);

    std::vector<glm::vec2> uvList{
            T0, T1, T3, T0, T3, T2, T0, T1, T3, T0, T3, T2,
            T0, T1, T3, T0, T3, T2, T0, T1, T3, T0, T3, T2,
            T0, T1, T3, T0, T3, T2, T0, T1, T3, T0, T3, T2
    };
    std::vector<GLfloat> uvData = Geometry::flatten(uvList);

    std::vector<glm::vec3> normalList{
            N1, N1, N1, N1, N1, N1, N2, N2, N2, N2, N2, N2,
            N3, N3, N3, N3, N3, N3, N4, N4, N4, N4, N4, N4,
            N5, N5, N5, N5, N5, N5, N6, N6, N6, N6, N6, N6
    };
    std::vector<GLfloat> normalData = Geometry::flatten(normalList);

    addAttribute("vertexPosition", Attribute::Type::Vec3, positionData);
    addAttribute("vertexColor", Attribute::Type::Vec3, colorData);
    addAttribute("vertexUV", Attribute::Type::Vec2, uvData);
    addAttribute("vertexNormal", Attribute::Type::Vec3, normalData);
    addAttribute("faceNormal", Attribute::Type::Vec3, normalData);

    m_vertexCount = 36;
}
