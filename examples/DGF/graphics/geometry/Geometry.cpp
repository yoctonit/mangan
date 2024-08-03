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

std::vector<float> Geometry::flatten(const std::vector<glm::vec2> &attributeList) {
    std::vector<float> data;
    for (auto &p: attributeList) {
        data.push_back(p.x);
        data.push_back(p.y);
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

glm::vec3 Geometry::calcNormal(glm::vec3 P0, glm::vec3 P1, glm::vec3 P2) {
    glm::vec3 v1 = P1 - P0;
    glm::vec3 v2 = P2 - P0;
    glm::vec3 normal = glm::cross(v1, v2);
    // normal.setLength(1);
    return glm::normalize(normal);
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

    // extract the rotation sub matrix
    auto rotationMatrix = glm::mat3(matrix);

    // update vertex normal data
    auto oldVertexNormalData = m_attributes["vertexNormal"].getData();
    std::vector<glm::vec3> oldVertexNormalList = Geometry::unflatten(oldVertexNormalData, 3);
    std::vector<glm::vec3> newVertexNormalList;
    for (auto &oldNormal: oldVertexNormalList) {
        glm::vec3 newNormal = rotationMatrix * oldNormal;
        newVertexNormalList.push_back(newNormal);
    }
    auto newVertexNormalData = Geometry::flatten(newVertexNormalList);
    m_attributes["vertexNormal"].uploadData(newVertexNormalData);

    // update face normal data
    auto oldFaceNormalData = m_attributes["faceNormal"].getData();
    std::vector<glm::vec3> oldFaceNormalList = Geometry::unflatten(oldFaceNormalData, 3);
    std::vector<glm::vec3> newFaceNormalList;
    for (auto &oldNormal: oldFaceNormalList) {
        glm::vec3 newNormal = rotationMatrix * oldNormal;
        newFaceNormalList.push_back(newNormal);
    }
    auto newFaceNormalData = Geometry::flatten(newFaceNormalList);
    m_attributes["faceNormal"].uploadData(newFaceNormalData);
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
