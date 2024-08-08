#ifndef DGF_GRAPHICS_CORE_OBJECT_3D_H
#define DGF_GRAPHICS_CORE_OBJECT_3D_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <map>
#include <vector>
#include <memory>
#include "../geometry/Geometry.h"
#include "../material/Material.h"


class Object3D {
public:
    explicit Object3D(const std::string &name);

    void add(const std::shared_ptr<Object3D> &child);

    void remove(const std::string &name);

    // calculate m_transformation of this Object3D relative
    // to the root Object3D of the scene graph
    [[nodiscard]] glm::mat4 getWorldMatrix() const;

    // return a single list containing all descendants
    std::vector<std::shared_ptr<Object3D>> getDescendentList() const;

    // apply geometric m_transformations
    void applyMatrix(glm::mat4 m, bool local);

    void lookAt(glm::vec3 targetPosition);

    void translate(float x, float y, float z, bool local);

    void rotateX(float angle, bool local);

    void rotateY(float angle, bool local);

    void rotateZ(float angle, bool local);

    void scale(float s, bool local);

    // get/set position components of m_transform
    glm::vec3 getPosition();

    [[nodiscard]] glm::vec3 getWorldPosition() const;

    void setPosition(glm::vec3 position);

    void setTransform(glm::mat4x4 t);

    [[nodiscard]] const std::string &name() const;

    [[nodiscard]] glm::mat4x4 transform() const;

    [[nodiscard]] Object3D *parent() const;

    void parent(Object3D *parent);

    [[nodiscard]] std::map<std::string, std::shared_ptr<Object3D>> &children();

    [[nodiscard]] bool isMesh() const;

    std::shared_ptr<Geometry> geometry();

    std::shared_ptr<Material> material();

    [[nodiscard]] bool isVisible() const;

    [[nodiscard]] GLuint vaoRef() const;

protected:
    std::string m_name;

    glm::mat4 m_transform{};

    Object3D *m_parent;

    std::map<std::string, std::shared_ptr<Object3D>> m_children;

    bool m_isMesh{false};

    // should this object be rendered?
    bool m_visible{false};

    std::shared_ptr<Geometry> m_geometry{nullptr};

    std::shared_ptr<Material> m_material{nullptr};

    // vertex array object reference
    GLuint m_vaoRef{};
};

#endif //DGF_GRAPHICS_CORE_OBJECT_3D_H
