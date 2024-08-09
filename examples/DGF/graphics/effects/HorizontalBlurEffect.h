#ifndef DGF_GRAPHICS_EFFECTS_HORIZONTAL_BLUR_EFFECT_H
#define DGF_GRAPHICS_EFFECTS_HORIZONTAL_BLUR_EFFECT_H

#include "../material/Material.h"


class HorizontalBlurEffect : public Material {
public:
    HorizontalBlurEffect(glm::vec2 textureSize, int blurRadius);
};

#endif //DGF_GRAPHICS_EFFECTS_HORIZONTAL_BLUR_EFFECT_H
