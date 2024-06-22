#include "Mesh.h"
#include <glad/glad.h>
#include <utility>

Mesh::Mesh(const std::string &name, std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material)
        : Object3D(name) {
    m_geometry = std::move(geometry);
    m_material = std::move(material);
    m_visible = true;
    m_isMesh = true;

    // set up associations between attributes stored in geometry and shader program stored in material
    glGenVertexArrays(1, &m_vaoRef);
    glBindVertexArray(m_vaoRef);

    for (auto &[attributeName, attribute]: m_geometry->attributes()) {
//        std::cout << attributeName << "\n";
        attribute.associateVariable(m_material->programRef(), attributeName);
    }

    // unbind this vertex array object
    glBindVertexArray(0);
}
