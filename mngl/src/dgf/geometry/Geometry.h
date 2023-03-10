//
// Created by ivan on 7.1.2023..
//

#ifndef INCLUDED_MN_GEOMETRY_H
#define INCLUDED_MN_GEOMETRY_H

#include <string>
#include <map>
#include <vector>
#include <utility>
#include <memory>
#include "Attribute.h"

class Geometry {
// Store Mn::Shader::Attribute objects,
// indexed by name of associated variable in shader.
// Shader variable associations set up later
// and stored in vertex array object in Mesh.
public:
    std::map<std::string, std::shared_ptr<Mn::Shader::Attribute>> attributes;
    int vertexCount;

    Geometry() : vertexCount{-1} {}

    void addAttribute(const std::string &variableName, const std::shared_ptr<Mn::Shader::Attribute> &attr) {
        attributes[variableName] = attr;
    }

    static std::vector<GLfloat> toVector(const std::vector<glm::vec3> &data) {
        std::vector<GLfloat> result;
        for (const auto &v: data) {
            result.push_back(v.x);
            result.push_back(v.y);
            result.push_back(v.z);
        }
        return result;
    }

    static std::vector<GLfloat> toVector(const std::vector<glm::vec2> &data) {
        std::vector<GLfloat> result;
        for (const auto &v: data) {
            result.push_back(v.x);
            result.push_back(v.y);
        }
        return result;
    }
};

#endif //INCLUDED_MN_GEOMETRY_H
