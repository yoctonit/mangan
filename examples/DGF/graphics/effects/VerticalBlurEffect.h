#ifndef DGF_GRAPHICS_EFFECTS_VERTICAL_BLUR_EFFECT_H
#define DGF_GRAPHICS_EFFECTS_VERTICAL_BLUR_EFFECT_H

#include "../material/Material.h"


class VerticalBlurEffect : public Material {
public:
    VerticalBlurEffect(glm::vec2 textureSize, int blurRadius);
};

#endif //DGF_GRAPHICS_EFFECTS_VERTICAL_BLUR_EFFECT_H
