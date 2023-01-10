//
// Created by ivan on 7.1.2023..
//

#ifndef OPENGL_EXAMPLES_GEOMETRY_H
#define OPENGL_EXAMPLES_GEOMETRY_H

#include <string>
#include <map>
#include <utility>
#include <vector>
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

    Geometry() : vertexCount{-1}   {}

    void addAttribute(const std::string& variableName, std::shared_ptr<Mn::Shader::Attribute> attr) {
        attributes[variableName] = attr;
    }
};

#endif //OPENGL_EXAMPLES_GEOMETRY_H
