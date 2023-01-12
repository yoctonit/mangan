//
// Created by ivan on 7.1.2023..
//

#ifndef INCLUDED_MN_POLYGON_H
#define INCLUDED_MN_POLYGON_H

#include <glm/glm.hpp>
#include <vector>
#include <cmath>
#include "Geometry.h"
#include "Attribute.h"

class Polygon : public Geometry {
public:
    Polygon(int sides, float radius) {
        if (sides < 3) sides = 3;
        float A = 2 * PI_F / (float)sides;

        std::vector<glm::vec3> positionList;
        std::vector<glm::vec3> colorList;

        glm::vec3 Z(0.0f,0.0f,0.0f);
        glm::vec3 C1(1.0f,1.0f,1.0f);
        glm::vec3 C2(1.0f,0.0f,0.0f);
        glm::vec3 C3(0.0f,0.0f,1.0f);

        for (int n = 0; n < sides; n++)
        {
            positionList.push_back( Z );
            positionList.emplace_back(radius * std::cos((float)n*A), radius * std::sin((float)n*A), 0.0f );
            positionList.emplace_back(radius * std::cos((float)(n+1)*A), radius * std::sin((float)(n+1)*A), 0.0f );
            colorList.push_back( C1 );
            colorList.push_back( C2 );
            colorList.push_back( C3 );
        }

        addAttribute("vertexPosition", std::make_shared<Mn::Shader::AttributeVector3>(toVector(positionList)));
        addAttribute("vertexColor", std::make_shared<Mn::Shader::AttributeVector3>(toVector(colorList)));
        vertexCount = sides * 3;
    }
};

#endif //INCLUDED_MN_POLYGON_H
