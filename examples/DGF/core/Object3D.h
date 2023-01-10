//
// Created by ivan on 7.1.2023..
//

#ifndef OPENGL_EXAMPLES_OBJECT3D_H
#define OPENGL_EXAMPLES_OBJECT3D_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <list>

class Object3D {
public:
    glm::mat4 transform{};
    Object3D *parent;
    std::list<Object3D *> children;

    Object3D() {
        transform = glm::mat4(1.0f);
        parent = nullptr;
    }

    void add(Object3D *child) {
        children.push_back(child);
        child->parent = this;
    }

    void remove(Object3D *child) {
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
//            return Matrix.multiply(parent.getWorldMatrix(), transform);
    }

    // return a single list containing all descendants
    std::list<Object3D *> getDescendentList() {
        std::list<Object3D *> descendents;
        // nodes to be added to descendant list,
        // and whose children will be added to this list
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
            // children of this node must also be processed
            for (Object3D *child: node->children)
                nodesToProcess.push_back(child);
        }
        return descendents;
    }

    // apply geometric transformations
    void applyMatrix(glm::mat4 m, bool local) {
        if (local)
            transform = m * transform;
//            transform.rightMultiply(m);
        else
            transform *= m;
//            transform.leftMultiply(m);
    }

    void translate(float x, float y, float z, bool local) {
        applyMatrix(glm::translate(glm::vec3(x, y, z)), local);
//        applyMatrix(glm::translate(x, y, z), local);
    }

    void rotateX(float angle, bool local) {
        applyMatrix(glm::rotate(angle, glm::vec3(1.0f, 0.0f, 0.0f)), local);
//        applyMatrix(glm::mat4.makeRotationX(angle), local);
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
        return {p[3], p[7], p[11]};
//        return new glm::vec3(
//                transform.values[0][3],
//                transform.values[1][3],
//                transform.values[2][3]);
    }

    [[nodiscard]] glm::vec3 getWorldPosition() const {
        glm::mat4 worldTransform = getWorldMatrix();
        float *p = glm::value_ptr(worldTransform);
        return {p[3], p[7], p[11]};
//        return glm::vec3(
//                worldTransform.values[0][3],
//                worldTransform.values[1][3],
//                worldTransform.values[2][3]);
    }

    void setPosition(glm::vec3 position) {
        float *p = glm::value_ptr(transform);
        p[3] = position.x;
        p[7] = position.y;
        p[11] = position.z;
//        transform.values[0][3] = position.values[0];
//        transform.values[1][3] = position.values[1];
//        transform.values[2][3] = position.values[2];
    }
};

#endif //OPENGL_EXAMPLES_OBJECT3D_H
