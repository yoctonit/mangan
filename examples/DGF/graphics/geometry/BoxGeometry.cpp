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

//    List positionList = Arrays.asList(
//            P5, P1, P3, P5, P3, P7, P0, P4, P6, P0, P6, P2,
//            P6, P7, P3, P6, P3, P2, P0, P1, P5, P0, P5, P4,
//            P4, P5, P7, P4, P7, P6, P1, P0, P2, P1, P2, P3);
//    float [] positionData = Vector.flattenList(positionList);
    std::vector<glm::vec3> positionList{
            P5, P1, P3, P5, P3, P7, P0, P4, P6, P0, P6, P2,
            P6, P7, P3, P6, P3, P2, P0, P1, P5, P0, P5, P4,
            P4, P5, P7, P4, P7, P6, P1, P0, P2, P1, P2, P3
    };
    std::vector<float> positionData;
    for (auto &p: positionList) {
        positionData.push_back(p.x);
        positionData.push_back(p.y);
        positionData.push_back(p.z);
    }

//    List colorList = Arrays.asList(
//            C1, C1, C1, C1, C1, C1, C2, C2, C2, C2, C2, C2,
//            C3, C3, C3, C3, C3, C3, C4, C4, C4, C4, C4, C4,
//            C5, C5, C5, C5, C5, C5, C6, C6, C6, C6, C6, C6);
//    float [] colorData = Vector.flattenList(colorList);
    std::vector<glm::vec3> colorList{
            C1, C1, C1, C1, C1, C1, C2, C2, C2, C2, C2, C2,
            C3, C3, C3, C3, C3, C3, C4, C4, C4, C4, C4, C4,
            C5, C5, C5, C5, C5, C5, C6, C6, C6, C6, C6, C6
    };
    std::vector<float> colorData;
    for (auto &c: colorList) {
        colorData.push_back(c.r);
        colorData.push_back(c.g);
        colorData.push_back(c.b);
    }

    addAttribute("vertexPosition", Attribute::Type::Vec3, positionData);
    addAttribute("vertexColor", Attribute::Type::Vec3, colorData);
    m_vertexCount = 36;
}
