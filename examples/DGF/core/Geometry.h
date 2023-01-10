//
// Created by ivan on 7.1.2023..
//

#ifndef OPENGL_EXAMPLES_GEOMETRY_H
#define OPENGL_EXAMPLES_GEOMETRY_H

#include <string>
#include <map>
#include <utility>
#include <vector>
#include "attribute.h"

class Geometry {
// Store Attribute objects,
// indexed by name of associated variable in shader.
// Shader variable associations set up later
// and stored in vertex array object in Mesh.
public:
    std::map<std::string, Attribute> attributes;
    int vertexCount;

    Geometry() : vertexCount{-1}   {}

    void addAttribute(Attribute::Type dataType, const std::string& variableName, std::vector<GLfloat> dataArray) {
        attributes[variableName] = Attribute(dataType, std::move(dataArray));
    }
};

#endif //OPENGL_EXAMPLES_GEOMETRY_H
