#include "Geometry.h"


Geometry::Geometry() = default;

void Geometry::addAttribute(const std::string &variableName, Attribute::Type dataType, std::vector<float> dataArray) {
    m_attributes[variableName] = Attribute(dataType, std::move(dataArray));
}

std::map<std::string, Attribute> &Geometry::attributes() {
    return m_attributes;
}

int Geometry::vertexCount() const {
    return m_vertexCount;
};

void Geometry::vertexCount(int count) {
    m_vertexCount = count;
}

std::vector<float> Geometry::flatten(const std::vector<glm::vec3> &attributeList) {
    std::vector<float> data;
    for (auto &p: attributeList) {
        data.push_back(p.x);
        data.push_back(p.y);
        data.push_back(p.z);
    }
    return data;
}

// transform vertex position data using a matrix
/*
void Geometry::applyMatrix(glm::mat4x4 matrix) {
    auto oldPositionData = attributes["vertexPosition"].getData();

    // convert flattened array back into list of vectors
    List <Vector> oldPositionList = Vector.unflattenList(oldPositionData, 3);
    List <Vector> newPositionList = new ArrayList<Vector>();

    for (Vector oldPos: oldPositionList) {
        // add homogeneous fourth coordinate
        oldPos.resize(4);
        oldPos.values[3] = 1;
        // multiply by matrix
        Vector newPos = matrix.multiplyVector(oldPos);
        // remove homogeneous coordinate
        newPos.resize(3);
        // add to new data list
        newPositionList.add(newPos);
    }

    float [] newPositionData = Vector.flattenList(newPositionList);
    attributes["vertexPosition"].getData() = newPositionData;
    // new data must be uploaded
    attributes.get("vertexPosition").uploadData();
}
*/

// merge data from attributes of other geometry into this object;
//   requires both geometries to have attributes with same names
/*
void Geometry::merge(Geometry other) {
    for (String variableName: attributes.keySet()) {
        // merge two arrays
        float []
        data1 = this.attributes.get(variableName).dataArray;
        float []
        data2 = other.attributes.get(variableName).dataArray;
        float []
        data3 = new float[data1.length + data2.length];
        for (int i = 0; i < data3.length; i++)
            if (i < data1.length)
                data3[i] = data1[i];
            else
                data3[i] = data2[i - data1.length];

        // new data must be set and uploaded
        this.attributes.get(variableName).dataArray = data3;
        this.attributes.get(variableName).uploadData();
    }
    // update the number of vertices
    this.vertexCount = this.vertexCount + other.vertexCount;
}
*/