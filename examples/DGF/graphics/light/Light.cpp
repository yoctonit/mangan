#include "Light.h"


Light::Light() {
    m_color = glm::vec3(1.0f, 1.0f, 1.0f);
    m_attenuation = glm::vec3(1.0f, 0.0f, 0.0f);
}

void Light::setUniforms(GLuint shaderId, int lightIndex) {
    std::string name;
    switch (lightIndex) {
        case 0:
            name = "light0";
            break;
        case 1:
            name = "light1";
            break;
        case 2:
            name = "light2";
            break;
        case 3:
            name = "light3";
            break;
        default:
            name = "";
    }

    int type;
    switch (m_type) {
        case Type::UNDEFINED:
            type = 0;
            break;
        case Type::AMBIENT:
            type = 1;
            break;
        case Type::DIRECTIONAL:
            type = 2;
            break;
        case Type::POINT:
            type = 3;
            break;
    }

    if (m_uniforms.find(name + ".lightType") != m_uniforms.end()) {
        m_uniforms[name + ".lightType"].data().m_dataInt = type;
    } else {
        m_uniforms[name + ".lightType"] = Uniform(shaderId, name + ".lightType", type);
    }

    if (m_uniforms.find(name + ".color") != m_uniforms.end()) {
        m_uniforms[name + ".color"].data().m_dataVec3 = m_color;
    } else {
        m_uniforms[name + ".color"] = Uniform(shaderId, name + ".color", m_color);
    }

    if (m_uniforms.find(name + ".direction") != m_uniforms.end()) {
        m_uniforms[name + ".direction"].data().m_dataVec3 = m_direction;
    } else {
        m_uniforms[name + ".direction"] = Uniform(shaderId, name + ".direction", m_direction);
    }

    if (m_uniforms.find(name + ".position") != m_uniforms.end()) {
        m_uniforms[name + ".position"].data().m_dataVec3 = m_position;
    } else {
        m_uniforms[name + ".position"] = Uniform(shaderId, name + ".position", m_position);
    }

    if (m_uniforms.find(name + ".attenuation") != m_uniforms.end()) {
        m_uniforms[name + ".attenuation"].data().m_dataVec3 = m_attenuation;
    } else {
        m_uniforms[name + ".attenuation"] = Uniform(shaderId, name + ".attenuation", m_attenuation);
    }
}

glm::vec3 Light::color() const {
    return m_color;
}

glm::vec3 Light::direction() const {
    return m_direction;
}

glm::vec3 Light::position() const {
    return m_position;
}

std::map<std::string, Uniform> &Light::uniforms() {
    return m_uniforms;
}
