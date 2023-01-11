//
// Created by ivan on 7.1.2023..
//

#ifndef INCLUDED_MN_RECTANGLE_H
#define INCLUDED_MN_RECTANGLE_H

#include <glm/glm.hpp>
#include <vector>
#include "Geometry.h"
#include "Attribute.h"

class Rectangle : public Geometry {
public:
//    Rectangle() = default;

    Rectangle(float width, float height) {
        glm::vec3 P0(-width / 2, -height / 2, 0.0f);
        glm::vec3 P1(width / 2, -height / 2, 0.0f);
        glm::vec3 P2(-width / 2, height / 2, 0.0f);
        glm::vec3 P3(width / 2, height / 2, 0.0f);
        glm::vec3 C0(1.0f, 1.0f, 1.0f);
        glm::vec3 C1(1.0f, 0.0f, 0.0f);
        glm::vec3 C2(0.0f, 1.0f, 0.0f);
        glm::vec3 C3(0.0f, 0.0f, 1.0f);

        const std::vector<GLfloat> positionData{
                P0.x, P0.y, P0.z,
                P1.x, P1.y, P1.z,
                P3.x, P3.y, P3.z,
                P0.x, P0.y, P0.z,
                P3.x, P3.y, P3.z,
                P2.x, P2.y, P2.z
        };

        const std::vector<GLfloat> colorData{
                C0.x, C0.y, C0.z,
                C1.x, C1.y, C1.z,
                C3.x, C3.y, C3.z,
                C0.x, C0.y, C0.z,
                C3.x, C3.y, C3.z,
                C2.x, C2.y, C2.z
        };

        addAttribute("vertexPosition", std::make_shared<Mn::Shader::AttributeVector3>(positionData));
        // addAttribute(Attribute::Type::Vec3, "vertexPosition", positionData);
        addAttribute("vertexColor", std::make_shared<Mn::Shader::AttributeVector3>(colorData));
        // addAttribute(Attribute::Type::Vec3, "vertexColor", colorData);
        vertexCount = 6;
    }
};

#endif //INCLUDED_MN_RECTANGLE_H
