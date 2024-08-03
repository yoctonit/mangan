#ifndef DGF_GRAPHICS_LIGHT_POINT_LIGHT_H
#define DGF_GRAPHICS_LIGHT_POINT_LIGHT_H

#include "Light.h"

class PointLight : public Light {
public:
    PointLight(glm::vec3 color, glm::vec3 position, glm::vec3 attenuation);

    PointLight(glm::vec3 color, glm::vec3 position);
};

#endif //DGF_GRAPHICS_LIGHT_POINT_LIGHT_H
