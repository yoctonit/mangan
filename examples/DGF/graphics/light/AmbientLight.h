#ifndef DGF_GRAPHICS_LIGHT_AMBIENT_LIGHT_H
#define DGF_GRAPHICS_LIGHT_AMBIENT_LIGHT_H

#include "Light.h"

class AmbientLight : public Light {
public:
    explicit AmbientLight(glm::vec3 color);
};

#endif //DGF_GRAPHICS_LIGHT_AMBIENT_LIGHT_H
