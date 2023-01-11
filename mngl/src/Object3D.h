//
// Created by ivan on 7.1.2023..
//

#ifndef INCLUDED_MN_OBJECT3D_H
#define INCLUDED_MN_OBJECT3D_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <list>
#include <memory>

class Object3D {
public:
    glm::mat4 transform{};
    std::shared_ptr<Object3D> parent{};
    std::list<std::shared_ptr<Object3D>> children;

    virtual bool isMesh() const { return false; }

    Object3D() {
        transform = glm::mat4(1.0f);
    }

    void add(const std::shared_ptr<Object3D>& child) {
        children.push_back(child);
        child->parent = std::make_shared<Object3D>(*this);
    }

    void remove(const std::shared_ptr<Object3D>& child) {
        children.remove(child);
        child->parent = nullptr;
    }

    // calculate transformation of this Object3D relative
    // to the root Object3D of the scene graph
    glm::mat4 getWorldMatrix() const {
        if (parent == nullptr)
            return transform;
        else
            return parent->getWorldMatrix() * transform;
    }

    // return a single list containing all descendants
    std::list<std::shared_ptr<Object3D>> getDescendentList() {
        std::list<std::shared_ptr<Object3D>> descendents;

        // nodes to be added to descendant list,
        // and whose children will be added to this list
        std::list<std::shared_ptr<Object3D>> nodesToProcess;
        nodesToProcess.push_back(std::make_shared<Object3D>(*this));

        // continue processing nodes while any are left
        while (!nodesToProcess.empty()) {
            // remove first node from list
            std::shared_ptr<Object3D> node = nodesToProcess.front();
            nodesToProcess.pop_front();

            // add this node to descendant list
            descendents.push_back(node);

            // children of this node must also be processed
            for (const std::shared_ptr<Object3D>& child: node->children)
                nodesToProcess.push_back(child);
        }
        return descendents;
    }

    // apply geometric transformations
    void applyMatrix(glm::mat4 m, bool local) {
        if (local)
            transform = m * transform;
        else
            transform *= m;
    }

    void translate(float x, float y, float z, bool local) {
        applyMatrix(glm::translate(glm::vec3(x, y, z)), local);
    }

    void rotateX(float angle, bool local) {
        applyMatrix(glm::rotate(angle, glm::vec3(1.0f, 0.0f, 0.0f)), local);
    }

    void rotateY(float angle, bool local) {
        applyMatrix(glm::rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f)), local);
    }

    void rotateZ(float angle, bool local) {
        applyMatrix(glm::rotate(angle, glm::vec3(0.0f, 0.0f, 1.0f)), local);
    }

    void scale(float s, bool local) {
        applyMatrix(glm::scale(glm::vec3(s, s, s)), local);
    }

// get/set position components of transform
    glm::vec3 getPosition() {
        float *p = glm::value_ptr(transform);
        return {p[12], p[13], p[14]};
//        return new glm::vec3(
//                transform.values[0][3],
//                transform.values[1][3],
//                transform.values[2][3]);
    }

    [[nodiscard]] glm::vec3 getWorldPosition() const {
        glm::mat4 worldTransform = getWorldMatrix();
        float *p = glm::value_ptr(worldTransform);
        return {p[12], p[13], p[14]};
//        return glm::vec3(
//                worldTransform.values[0][3],
//                worldTransform.values[1][3],
//                worldTransform.values[2][3]);
    }

    void setPosition(glm::vec3 position) {
        float *p = glm::value_ptr(transform);
        p[12] = position.x;
        p[13] = position.y;
        p[14] = position.z;
//        transform.values[0][3] = position.values[0];
//        transform.values[1][3] = position.values[1];
//        transform.values[2][3] = position.values[2];
    }
};

#endif //INCLUDED_MN_OBJECT3D_H
