#ifndef DGF_GRAPHICS_LIGHT_LIGHT_H
#define DGF_GRAPHICS_LIGHT_LIGHT_H

#include <string>
#include <map>
#include <glm/vec3.hpp>
#include "../core/Uniform.h"

class Light {
public:
    enum class Type {
        UNDEFINED, AMBIENT, DIRECTIONAL, POINT
    };

    Light();

    [[nodiscard]] std::map<std::string, Uniform> &uniforms();

    void setUniforms(GLuint shaderId, int lightIndex);

protected:
    Type m_type{Type::UNDEFINED};
    glm::vec3 m_color{};
    glm::vec3 m_attenuation{};
    glm::vec3 m_direction{};
    glm::vec3 m_position{};

    // Store Uniform objects, indexed by name of associated variable in shader.
    std::map<std::string, Uniform> m_uniforms;
};

#endif //DGF_GRAPHICS_LIGHT_LIGHT_H
