#include <glm/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Object3D.h"

Object3D::Object3D() {
    m_transform = glm::mat4(1.0f);
    m_parent = nullptr;
}

void Object3D::add(Object3D *child) {
    m_children.push_back(child);
    child->m_parent = this;
}

void Object3D::remove(Object3D *child) {
    m_children.remove(child);
    child->m_parent = nullptr;
}

// calculate m_transformation of this Object3D relative
// to the root Object3D of the scene graph
glm::mat4 Object3D::getWorldMatrix() const {
    if (m_parent == nullptr)
        return m_transform;
    else
        return m_parent->getWorldMatrix() * m_transform;
//            return Matrix.multiply(m_parent.getWorldMatrix(), m_transform);
}

// return a single list containing all descendants
std::list<Object3D *> Object3D::getDescendentList() {
    std::list<Object3D *> descendents;
    // nodes to be added to descendant list,
    // and whose m_children will be added to this list
    std::list<Object3D *> nodesToProcess;
    nodesToProcess.push_back(this);
    // continue processing nodes while any are left
    while (!nodesToProcess.empty()) {
        // remove first node from list
        Object3D *node = nodesToProcess.front();
        nodesToProcess.pop_front();
        //            Object3D node = nodesToProcess.remove(0);
        // add this node to descendant list
        descendents.push_back(node);
        // m_children of this node must also be processed
        for (Object3D *child: node->m_children)
            nodesToProcess.push_back(child);
    }
    return descendents;
}

// apply geometric m_transformations
void Object3D::applyMatrix(glm::mat4 m, bool local) {
    if (local)
        m_transform = m * m_transform;
//            m_transform.rightMultiply(m);
    else
        m_transform *= m;
//            m_transform.leftMultiply(m);
}

void Object3D::translate(float x, float y, float z, bool local) {
    applyMatrix(glm::translate(glm::vec3(x, y, z)), local);
//        applyMatrix(glm::translate(x, y, z), local);
}

void Object3D::rotateX(float angle, bool local) {
    applyMatrix(glm::rotate(angle, glm::vec3(1.0f, 0.0f, 0.0f)), local);
//        applyMatrix(glm::mat4.makeRotationX(angle), local);
}

void Object3D::rotateY(float angle, bool local) {
    applyMatrix(glm::rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f)), local);
}

void Object3D::rotateZ(float angle, bool local) {
    applyMatrix(glm::rotate(angle, glm::vec3(0.0f, 0.0f, 1.0f)), local);
}

void Object3D::scale(float s, bool local) {
    applyMatrix(glm::scale(glm::vec3(s, s, s)), local);
}

// get/set position components of m_transform
glm::vec3 Object3D::getPosition() {
    float *p = glm::value_ptr(m_transform);
    return {p[3], p[7], p[11]};
//        return new glm::vec3(
//                m_transform.values[0][3],
//                m_transform.values[1][3],
//                m_transform.values[2][3]);
}

[[nodiscard]] glm::vec3 Object3D::getWorldPosition() const {
    glm::mat4 worldTransform = getWorldMatrix();
    float *p = glm::value_ptr(worldTransform);
    return {p[3], p[7], p[11]};
//        return glm::vec3(
//                worldTransform.values[0][3],
//                worldTransform.values[1][3],
//                worldTransform.values[2][3]);
}

void Object3D::setPosition(glm::vec3 position) {
    float *p = glm::value_ptr(m_transform);
    p[3] = position.x;
    p[7] = position.y;
    p[11] = position.z;
//        m_transform.values[0][3] = position.values[0];
//        m_transform.values[1][3] = position.values[1];
//        m_transform.values[2][3] = position.values[2];
}
