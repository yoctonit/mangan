#ifndef DGF_GRAPHICS_GEOMETRY_GEOMETRY_H
#define DGF_GRAPHICS_GEOMETRY_GEOMETRY_H

#include <map>
#include <memory>
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

    void vertexCount(int count);

    static std::vector<float> flatten(const std::vector<glm::vec3> &attributeList);

    static std::vector<float> flatten(const std::vector<glm::vec2> &attributeList);

    static std::vector<glm::vec3> unflatten(std::vector<float>, int vecSize = 3);

    static glm::vec3 calcNormal(glm::vec3 P0, glm::vec3 P1, glm::vec3 P2);

    // transform vertex position data using a matrix
    void applyMatrix(glm::mat4x4 matrix);

    // merge data from attributes of other geometry into this object;
    // requires both geometries to have attributes with same names
    void merge(const std::shared_ptr<Geometry> &other);

protected:
    // Store Attribute objects,
    // indexed by name of associated variable in shader.
    // Shader variable associations set up later
    // and stored in vertex array object in Mesh.
    std::map<std::string, Attribute> m_attributes;
    int m_vertexCount{-1};
};

#endif //DGF_GRAPHICS_GEOMETRY_GEOMETRY_H
