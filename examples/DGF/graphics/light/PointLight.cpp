#include "PointLight.h"

PointLight::PointLight(glm::vec3 color, glm::vec3 position, glm::vec3 attenuation) {
    m_type = Type::POINT;
    m_color = color;
    m_position = position;
    m_attenuation = attenuation;
}

PointLight::PointLight(glm::vec3 color, glm::vec3 position) {
    m_type = Type::POINT;
    m_color = color;
    m_position = position;
    m_attenuation = glm::vec3(1.0f, 0.0f, 0.1f);
}

void PointLight::setPosition(glm::vec3 position) {
    m_position = position;
}