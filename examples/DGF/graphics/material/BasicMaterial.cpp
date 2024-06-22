#include "BasicMaterial.h"

BasicMaterial::BasicMaterial()
        : Material("shader/BasicMaterial.vert", "shader/BasicMaterial.frag") {
    addUniform("baseColor", glm::vec3(1.0f, 1.0f, 1.0f));
    addUniform("useVertexColors", false);
}
