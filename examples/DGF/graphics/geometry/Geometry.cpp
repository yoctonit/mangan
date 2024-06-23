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

std::vector<glm::vec3> Geometry::unflatten(std::vector<float> flatArray, int vecSize) {
    std::vector<glm::vec3> vecList;

    for (int i = 0; i < flatArray.size(); i += vecSize) {
        vecList.emplace_back(flatArray[i + 0], flatArray[i + 1], flatArray[i + 2]);
    }

    return vecList;
}

// transform vertex position data using a matrix
void Geometry::applyMatrix(glm::mat4x4 matrix) {
    auto oldPositionData = m_attributes["vertexPosition"].getData();

    // convert flattened array back into list of vectors
    std::vector<glm::vec3> oldPositionList = Geometry::unflatten(oldPositionData);
    std::vector<glm::vec3> newPositionList;

    for (auto &oldPos: oldPositionList) {
        // add homogeneous fourth coordinate
        glm::vec4 tmp(oldPos, 1.0f);
        // multiply by matrix
        glm::vec4 newPos = matrix * tmp;
        // remove homogeneous coordinate, and add to new data list
        newPositionList.emplace_back(newPos.x, newPos.y, newPos.z);
    }

    auto newPositionData = Geometry::flatten(newPositionList);
    // new data must be uploaded
    m_attributes["vertexPosition"].uploadData(newPositionData);
}

// merge data from attributes of other geometry into this object;
// requires both geometries to have attributes with same names
void Geometry::merge(const std::shared_ptr<Geometry> &other) {
    for (auto &[name, attr]: m_attributes) {
        auto data1 = attr.getData();
        auto data2 = other->m_attributes[name].getData();
        std::vector<float> data3;
        data3.insert(std::end(data3), std::begin(data1), std::end(data1));
        data3.insert(std::end(data3), std::begin(data2), std::end(data2));

        m_attributes[name].uploadData(data3);
    }
    m_vertexCount += other->m_vertexCount;

//    for (String variableName: attributes.keySet()) {
//        // merge two arrays
//        float [] data1 = this.attributes.get(variableName).dataArray;
//        float [] data2 = other.attributes.get(variableName).dataArray;
//        float [] data3 = new float[data1.length + data2.length];
//        for (int i = 0; i < data3.length; i++)
//            if (i < data1.length)
//                data3[i] = data1[i];
//            else
//                data3[i] = data2[i - data1.length];
//
//        // new data must be set and uploaded
//        this.attributes.get(variableName).dataArray = data3;
//        this.attributes.get(variableName).uploadData();
//    }
//    // update the number of vertices
//    this.vertexCount = this.vertexCount + other.vertexCount;
}
