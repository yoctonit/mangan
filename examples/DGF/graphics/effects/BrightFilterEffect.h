#ifndef DGF_GRAPHICS_EFFECTS_BRIGHT_FILTER_EFFECT_H
#define DGF_GRAPHICS_EFFECTS_BRIGHT_FILTER_EFFECT_H

#include "../material/Material.h"


class BrightFilterEffect : public Material {
public:
    explicit BrightFilterEffect(float threshold);
};

#endif //DGF_GRAPHICS_EFFECTS_BRIGHT_FILTER_EFFECT_H
