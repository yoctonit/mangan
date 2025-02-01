//
// Created by ivan on 2.6.2020.
//

#ifndef INCLUDED_POSITIONAL_LIGHT_H
#define INCLUDED_POSITIONAL_LIGHT_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class point_light {

public:
    point_light();

    [[nodiscard]] glm::vec4 position() const { return _position; }

    void position(glm::vec4 p) { _position = p; }

    [[nodiscard]] glm::vec3 ambient() const { return _ambient; }

    void ambient(glm::vec3 intensity) { _ambient = intensity; }

    [[nodiscard]] glm::vec3 diffuse() const { return _diffuse; }

    void diffuse(glm::vec3 intensity) { _diffuse = intensity; }

    [[nodiscard]] glm::vec3 specular() const { return _specular; }

    void specular(glm::vec3 intensity) { _specular = intensity; }

private:
    glm::vec4 _position{}; // In world coordinates.
    glm::vec3 _ambient{};
    glm::vec3 _diffuse{};
    glm::vec3 _specular{};
};

#endif //INCLUDED_POSITIONAL_LIGHT_H
