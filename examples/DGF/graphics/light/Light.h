#ifndef DGF_GRAPHICS_LIGHT_LIGHT_H
#define DGF_GRAPHICS_LIGHT_LIGHT_H

#include <glm/vec3.hpp>

class Light {
public:
    enum class Type {
        UNDEFINED, AMBIENT, DIRECTIONAL, POINT
    };

    Light();

protected:
    Type m_type{Type::UNDEFINED};
    glm::vec3 m_color{};
    glm::vec3 m_attenuation{};
    glm::vec3 m_direction{};
    glm::vec3 m_position{};
};

#endif //DGF_GRAPHICS_LIGHT_LIGHT_H
