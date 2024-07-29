#ifndef DGF_GRAPHICS_EFFECTS_VIGNETTE_EFFECT_H
#define DGF_GRAPHICS_EFFECTS_VIGNETTE_EFFECT_H

#include "../material/Material.h"


class VignetteEffect : public Material {
public:
    VignetteEffect(float dimStart, float dimEnd, glm::vec3 dimColor);
};

#endif //DGF_GRAPHICS_EFFECTS_VIGNETTE_EFFECT_H
