#ifndef DGF_GRAPHICS_EFFECTS_ADDITIVE_BLEND_EFFECT_H
#define DGF_GRAPHICS_EFFECTS_ADDITIVE_BLEND_EFFECT_H

#include "../core/Texture.h"
#include "../material/Material.h"


class AdditiveBlendEffect : public Material {
public:
    AdditiveBlendEffect(const std::shared_ptr<Texture> &blendTexture, float originalStrength, float blendStrength);
};

#endif //DGF_GRAPHICS_EFFECTS_ADDITIVE_BLEND_EFFECT_H
