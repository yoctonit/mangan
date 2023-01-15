//
// Created by ivan on 7.1.2023..
//

#ifndef INCLUDED_MN_BOX_H
#define INCLUDED_MN_BOX_H

#include "glm/glm.hpp"
#include <vector>
#include "Geometry.h"
#include "Attribute.h"

class Box : public Geometry {
public:
    Box(float width, float height, float depth) {
        // corners of a cube
        glm::vec3 P0(-width/2, -height/2, -depth/2);
        glm::vec3 P1( width/2, -height/2, -depth/2);
        glm::vec3 P2(-width/2, height/2, -depth/2);
        glm::vec3 P3( width/2, height/2, -depth/2);
        glm::vec3 P4(-width/2, -height/2, depth/2);
        glm::vec3 P5( width/2, -height/2, depth/2);
        glm::vec3 P6(-width/2, height/2, depth/2);
        glm::vec3 P7( width/2, height/2, depth/2);

        // colors for faces in order: x+, x-, y+, y-, z+, z-
        glm::vec3 C1(1.0f, 0.5f, 0.5f);
        glm::vec3 C2(0.5f, 0.0f, 0.0f);
        glm::vec3 C3(0.5f, 1.0f, 0.5f);
        glm::vec3 C4(0.0f, 0.5f, 0.0f);
        glm::vec3 C5(0.5f, 0.5f, 1.0f);
        glm::vec3 C6(0.0f, 0.0f, 0.5f);

//        const std::vector<GLfloat> positionData{
//                P5.x,P5.y,P5.z,P1.x,P1.y,P1.z,P3.x,P3.y,P3.z,P5.x,P5.y,P5.z,P3.x,P3.y,P3.z,P7.x,P7.y,P7.z,
//                P0.x,P0.y,P0.z,P4.x,P4.y,P4.z,P6.x,P6.y,P6.z,P0.x,P0.y,P0.z,P6.x,P6.y,P6.z,P2.x,P2.y,P2.z,
//                P6.x,P6.y,P6.z,P7.x,P7.y,P7.z,P3.x,P3.y,P3.z,P6.x,P6.y,P6.z,P3.x,P3.y,P3.z,P2.x,P2.y,P2.z,
//                P0.x,P0.y,P0.z,P1.x,P1.y,P1.z,P5.x,P5.y,P5.z,P0.x,P0.y,P0.z,P5.x,P5.y,P5.z,P4.x,P4.y,P4.z,
//                P4.x,P4.y,P4.z,P5.x,P5.y,P5.z,P7.x,P7.y,P7.z,P4.x,P4.y,P4.z,P7.x,P7.y,P7.z,P6.x,P6.y,P6.z,
//                P1.x,P1.y,P1.z,P0.x,P0.y,P0.z,P2.x,P2.y,P2.z,P1.x,P1.y,P1.z,P2.x,P2.y,P2.z,P3.x,P3.y,P3.z
//        };
//
//        const std::vector<GLfloat> colorData{
//                C1.x,C1.y,C1.z,C1.x,C1.y,C1.z,C1.x,C1.y,C1.z,C1.x,C1.y,C1.z,C1.x,C1.y,C1.z,C1.x,C1.y,C1.z,
//                C2.x,C2.y,C2.z,C2.x,C2.y,C2.z,C2.x,C2.y,C2.z,C2.x,C2.y,C2.z,C2.x,C2.y,C2.z,C2.x,C2.y,C2.z,
//                C3.x,C3.y,C3.z,C3.x,C3.y,C3.z,C3.x,C3.y,C3.z,C3.x,C3.y,C3.z,C3.x,C3.y,C3.z,C3.x,C3.y,C3.z,
//                C4.x,C4.y,C4.z,C4.x,C4.y,C4.z,C4.x,C4.y,C4.z,C4.x,C4.y,C4.z,C4.x,C4.y,C4.z,C4.x,C4.y,C4.z,
//                C5.x,C5.y,C5.z,C5.x,C5.y,C5.z,C5.x,C5.y,C5.z,C5.x,C5.y,C5.z,C5.x,C5.y,C5.z,C5.x,C5.y,C5.z,
//                C6.x,C6.y,C6.z,C6.x,C6.y,C6.z,C6.x,C6.y,C6.z,C6.x,C6.y,C6.z,C6.x,C6.y,C6.z,C6.x,C6.y,C6.z
//        };

        const std::vector<glm::vec3> positionList{
                P5,P1,P3,P5,P3,P7, P0,P4,P6,P0,P6,P2,
                P6,P7,P3,P6,P3,P2, P0,P1,P5,P0,P5,P4,
                P4,P5,P7,P4,P7,P6, P1,P0,P2,P1,P2,P3 };
        const std::vector<glm::vec3> colorList {
                C1,C1,C1,C1,C1,C1, C2,C2,C2,C2,C2,C2,
                C3,C3,C3,C3,C3,C3, C4,C4,C4,C4,C4,C4,
                C5,C5,C5,C5,C5,C5, C6,C6,C6,C6,C6,C6 };

        addAttribute("vertexPosition", std::make_shared<Mn::Shader::AttributeVector3>(toVector(positionList)));
        addAttribute("vertexColor", std::make_shared<Mn::Shader::AttributeVector3>(toVector(colorList)));
        vertexCount = 36;
    }
};

#endif //INCLUDED_MN_BOX_H
