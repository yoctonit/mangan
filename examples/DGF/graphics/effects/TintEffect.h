#ifndef DGF_GRAPHICS_EFFECTS_TINT_EFFECT_H
#define DGF_GRAPHICS_EFFECTS_TINT_EFFECT_H

#include "../material/Material.h"


class TintEffect : public Material {
public:
    explicit TintEffect(glm::vec3 tintColor);
};

#endif //DGF_GRAPHICS_EFFECTS_TINT_EFFECT_H
