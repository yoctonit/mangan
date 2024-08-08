#include <glm/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Object3D.h"

Object3D::Object3D(const std::string &name) {
    m_name = name;
    m_transform = glm::mat4(1.0f);
    m_parent = nullptr;
}

void Object3D::add(const std::shared_ptr<Object3D> &child) {
    m_children[child->name()] = child;
    child->parent(this);
}

void Object3D::remove(const std::string &name) {
    if (m_children.find(name) == m_children.end()) {
        std::cerr << "Object3D::remove not found child with name " << name << "\n";
    }
    m_children[name]->parent(nullptr);
    m_children.erase(name);
}

// calculate m_transformation of this Object3D relative
// to the root Object3D of the scene graph
glm::mat4 Object3D::getWorldMatrix() const {
    if (m_parent == nullptr)
        return m_transform;
    else
        return m_parent->getWorldMatrix() * m_transform;
}

// return a single list containing all descendants
std::vector<std::shared_ptr<Object3D>> Object3D::getDescendentList() const {
    std::vector<std::shared_ptr<Object3D>> descendents;

    // nodes to be added to descendant list,
    // and whose m_children will be added to this list
    std::vector<std::shared_ptr<Object3D>> nodesToProcess;
    nodesToProcess.reserve(m_children.size());
    for (auto &[name, object]: m_children) {
        nodesToProcess.push_back(object);
    }

    // continue processing nodes while any are left
    while (!nodesToProcess.empty()) {
        // remove first node from list
        auto node = nodesToProcess.front();

        // add this node to descendant list
        descendents.push_back(node);

        // children of this node must also be processed
        for (auto &[name, object]: node->children()) {
            nodesToProcess.push_back(object);
        }

        nodesToProcess.erase(nodesToProcess.begin());
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

// does not work (yet)!
void Object3D::lookAt(glm::vec3 targetPosition) {
    // m_transform = Matrix.makeLookAt(getWorldPosition(), targetPosition );
    m_transform = glm::lookAt(getWorldPosition(), targetPosition, glm::vec3(0.0f, 1.0f, 0.0f));
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

void Object3D::setTransform(glm::mat4x4 t) {
    m_transform = t;
}

const std::string &Object3D::name() const {
    return m_name;
}

glm::mat4x4 Object3D::transform() const {
    return m_transform;
}

Object3D *Object3D::parent() const {
    return m_parent;
}

void Object3D::parent(Object3D *parent) {
    m_parent = parent;
}

std::map<std::string, std::shared_ptr<Object3D>> &Object3D::children() {
    return m_children;
}

[[nodiscard]] bool Object3D::isMesh() const {
    return m_isMesh;
}

std::shared_ptr<Geometry> Object3D::geometry() {
    return m_geometry;
}

std::shared_ptr<Material> Object3D::material() {
    return m_material;
}

bool Object3D::isVisible() const {
    return m_visible;
}

GLuint Object3D::vaoRef() const {
    return m_vaoRef;
}
