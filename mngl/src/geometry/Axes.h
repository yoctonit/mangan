//
// Created by ivan on 7.1.2023..
//

#ifndef INCLUDED_MN_AXES_H
#define INCLUDED_MN_AXES_H

#include <glm/glm.hpp>
#include <vector>
#include "../Mesh.h"
#include "Geometry.h"
#include "../material/LineMaterial.h"
#include "Attribute.h"

class Axes : public Geometry {
public:
    explicit Axes(float axisLength) {
        const std::vector<glm::vec3> positionList{
                glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(axisLength, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, axisLength, 0.0f),
                glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, axisLength)
        };

//        const std::vector<glm::vec3> colorList{
//                glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(0.5f, 1.0f, 0.5f),
//                glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(1.0f, 0.5f, 0.5f),
//                glm::vec3(0.0f, 0.0f, 0.5f), glm::vec3(0.5f, 0.5f, 1.0f)
//        };
        const std::vector<glm::vec3> colorList{
                glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(0.5f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f, 0.5f, 0.0f),
                glm::vec3(0.0f, 0.0f, 0.5f), glm::vec3(0.0f, 0.0f, 0.5f)
        };

        addAttribute("vertexPosition", std::make_shared<Mn::Shader::AttributeVector3>(toVector(positionList)));
        addAttribute("vertexColor", std::make_shared<Mn::Shader::AttributeVector3>(toVector(colorList)));
        vertexCount = 6;
    }
};

class AxesHelper : public Mesh {
public:
    AxesHelper(float axisLength, int lineWidth)
            : Mesh(std::make_shared<Axes>(axisLength), std::make_shared<LineMaterial>()) {
//    material->uniforms.get("useVertexColors").data = 1;
        material->useVertexColors(true);
        material->renderSettings["lineWidth"] = RenderSetting("lineWidth", (float) lineWidth, true);
    }
};

class GridGeometry : public Geometry {
public:
    GridGeometry(float size, int divisions, glm::vec3 gridColor, glm::vec3 centerColor) {
        float deltaSize = size / (float) divisions;
        std::vector<float> values;
        for (int n = 0; n < divisions + 1; n++)
            values.push_back(-size / 2 + (float) n * deltaSize);
        std::vector<glm::vec3> positionList;
        std::vector<glm::vec3> colorList;
        // add vertical lines
        for (float x: values) {
            positionList.emplace_back(x, -size / 2, 0.0f);
            positionList.emplace_back(x, size / 2, 0.0f);
            if (x == 0) {
                colorList.push_back(centerColor);
                colorList.push_back(centerColor);
            } else {
                colorList.push_back(gridColor);
                colorList.push_back(gridColor);
            }
        }
        // add horizontal lines
        for (float y: values) {
            positionList.emplace_back(-size / 2, y, 0.0f);
            positionList.emplace_back(size / 2, y, 0.0f);
            if (y == 0) {
                colorList.push_back(centerColor);
                colorList.push_back(centerColor);
            } else {
                colorList.push_back(gridColor);
                colorList.push_back(gridColor);
            }
        }
        addAttribute("vertexPosition", std::make_shared<Mn::Shader::AttributeVector3>(toVector(positionList)));
        addAttribute("vertexColor", std::make_shared<Mn::Shader::AttributeVector3>(toVector(colorList)));
        vertexCount = (int) positionList.size();
    }

    GridGeometry() : GridGeometry(10.0f, 10, glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.8f, 0.8f, 0.8f)) {}
};

class GridHelper : public Mesh {
public:

    GridHelper(float size, int divisions, glm::vec3 gridColor, glm::vec3 centerColor, int lineWidth)
            : Mesh(std::make_shared<GridGeometry>(size, divisions, gridColor, centerColor),
                   std::make_shared<LineMaterial>()) {
        material->useVertexColors(true);
        material->renderSettings["lineWidth"] = RenderSetting("lineWidth", (float) lineWidth, true);
    }

    GridHelper() : GridHelper(10.0f, 10, glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.8f, 0.8f, 0.8f), 1) {
    }

};

#endif //INCLUDED_MN_AXES_H
