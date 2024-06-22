#ifndef DGF_GRAPHICS_GEOMETRY_GEOMETRY_H
#define DGF_GRAPHICS_GEOMETRY_GEOMETRY_H

#include <map>
#include <string>
#include <vector>
#include <glm/mat4x4.hpp>
#include "../core/Attribute.h"

class Geometry {
public:
    Geometry();

    void addAttribute(const std::string &variableName, Attribute::Type dataType, std::vector<float> dataArray);

    std::map<std::string, Attribute> &attributes();

    [[nodiscard]] int vertexCount() const;

    // transform vertex position data using a matrix
    // void applyMatrix(glm::mat4x4 matrix);

    // merge data from attributes of other geometry into this object;
    //   requires both geometries to have attributes with same names
    // void merge(Geometry other);
protected:
    // Store Attribute objects,
    // indexed by name of associated variable in shader.
    // Shader variable associations set up later
    // and stored in vertex array object in Mesh.
    std::map<std::string, Attribute> m_attributes;
    int m_vertexCount{-1};
};

#endif //DGF_GRAPHICS_GEOMETRY_GEOMETRY_H
