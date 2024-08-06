#ifndef DGF_GRAPHICS_LIGHT_DIRECTIONAL_LIGHT_H
#define DGF_GRAPHICS_LIGHT_DIRECTIONAL_LIGHT_H

#include "Light.h"

class DirectionalLight : public Light {
public:
    DirectionalLight(glm::vec3 color, glm::vec3 direction);

    void setDirection(glm::vec3 direction);
};

#endif //DGF_GRAPHICS_LIGHT_DIRECTIONAL_LIGHT_H
