#include "AmbientLight.h"

AmbientLight::AmbientLight(glm::vec3 color) {
    m_type = Type::AMBIENT;
    m_color = color;
}
