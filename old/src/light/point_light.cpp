//
// Created by ivan on 2.6.2020..
//

#include "point_light.h"

namespace mn {

    point_light::point_light() {
        _position = glm::vec4(10.0f, 10.0f, 10.0f, 1.0f);
        _ambient = glm::vec3(0.2f, 0.2f, 0.2f);
        _diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
        _specular = glm::vec3(1.0f, 1.0f, 1.0f);
    }

}