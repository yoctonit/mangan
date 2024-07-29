#ifndef DGF_GRAPHICS_EFFECTS_PIXELATE_EFFECT_H
#define DGF_GRAPHICS_EFFECTS_PIXELATE_EFFECT_H

#include "../material/Material.h"


class PixelateEffect : public Material {
public:
    PixelateEffect(float pixelSize, glm::vec2 resolution);
};

#endif //DGF_GRAPHICS_EFFECTS_PIXELATE_EFFECT_H
