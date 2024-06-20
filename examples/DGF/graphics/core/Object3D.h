#ifndef DGF_GRAPHICS_CORE_OBJECT_3D_H
#define DGF_GRAPHICS_CORE_OBJECT_3D_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <list>

class Object3D {
public:
    glm::mat4 m_transform{};
    Object3D *m_parent;
    std::list<Object3D *> m_children;

    Object3D();

    void add(Object3D *child);

    void remove(Object3D *child);

    // calculate m_transformation of this Object3D relative
    // to the root Object3D of the scene graph
    [[nodiscard]] glm::mat4 getWorldMatrix() const;

    // return a single list containing all descendants
    std::list<Object3D *> getDescendentList();

    // apply geometric m_transformations
    void applyMatrix(glm::mat4 m, bool local);

    void translate(float x, float y, float z, bool local);

    void rotateX(float angle, bool local);

    void rotateY(float angle, bool local);

    void rotateZ(float angle, bool local);

    void scale(float s, bool local);

    // get/set position components of m_transform
    glm::vec3 getPosition();

    [[nodiscard]] glm::vec3 getWorldPosition() const;

    void setPosition(glm::vec3 position);
};

#endif //DGF_GRAPHICS_CORE_OBJECT_3D_H
