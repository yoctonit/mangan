#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 color, glm::vec3 direction) {
    m_type = Type::DIRECTIONAL;
    m_color = color;
    m_direction = direction;
}

void DirectionalLight::setDirection(glm::vec3 direction) {
    m_direction = direction;
}
