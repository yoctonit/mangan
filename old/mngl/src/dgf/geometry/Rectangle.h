//
// Created by ivan on 7.1.2023..
//

#ifndef INCLUDED_MN_RECTANGLE_H
#define INCLUDED_MN_RECTANGLE_H

#include "glm/glm.hpp"
#include <vector>
#include "Geometry.h"
#include "Attribute.h"

class Rectangle : public Geometry {
public:
    Rectangle(float width, float height)
            : _position(glm::vec2(0.0f, 0.0f)), _alignment(glm::vec2(0.5f, 0.5f)) {
        float x = _position.x;
        float y = _position.y;
        float a = _alignment.x;
        float b = _alignment.y;

        glm::vec3 P0(x + (-a) * width, y + (-b) * height, 0.0f);
        glm::vec3 P1(x + (1 - a) * width, y + (-b) * height, 0.0f);
        glm::vec3 P2(x + (-a) * width, y + (1 - b) * height, 0.0f);
        glm::vec3 P3(x + (1 - a) * width, y + (1 - b) * height, 0.0f);
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

        // texture coordinates
        glm::vec2 T0(0.0f, 0.0f);
        glm::vec2 T1(1.0f, 0.0f);
        glm::vec2 T2(0.0f, 1.0f);
        glm::vec2 T3(1.0f, 1.0f);
        const std::vector<glm::vec2> uvList{T0, T1, T3, T0, T3, T2};
//        float[] uvData = Vector.flattenList(uvList);
//        addAttribute("vec2", "vertexUV", uvData);

        // normal vector
        glm::vec3 N0(0.0f, 0.0f, 1.0f);
        const std::vector<glm::vec3> normalList{N0, N0, N0, N0, N0, N0};
        // float[] normalData = Vector.flattenList(normalList);
//        addAttribute("vec3", "vertexNormal", normalData);
//        addAttribute("vec3", "faceNormal", normalData);

        addAttribute("vertexPosition", std::make_shared<Mn::Shader::AttributeVector3>(positionData));
        // addAttribute(Attribute::Type::Vec3, "vertexPosition", positionData);
        addAttribute("vertexColor", std::make_shared<Mn::Shader::AttributeVector3>(colorData));
        // addAttribute(Attribute::Type::Vec3, "vertexColor", colorData);
        addAttribute("vertexUV", std::make_shared<Mn::Shader::AttributeVector2>(toVector(uvList)));
        addAttribute("vertexNormal", std::make_shared<Mn::Shader::AttributeVector3>(toVector(normalList)));
        addAttribute("faceNormal", std::make_shared<Mn::Shader::AttributeVector3>(toVector(normalList)));
        vertexCount = 6;
    }

    void position(glm::vec2 p) { _position = p; }

    void alignment(glm::vec2 a) { _alignment = a; }

private:
    glm::vec2 _position;
    glm::vec2 _alignment;
};

#endif //INCLUDED_MN_RECTANGLE_H
