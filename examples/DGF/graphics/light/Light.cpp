#include "Light.h"

Light::Light() {
    m_color = glm::vec3(1.0f, 1.0f, 1.0f);
    m_attenuation = glm::vec3(1.0f, 0.0f, 0.0f);
}
