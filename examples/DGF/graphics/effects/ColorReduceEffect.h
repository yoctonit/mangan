#ifndef DGF_GRAPHICS_EFFECTS_COLOR_REDUCE_EFFECT_H
#define DGF_GRAPHICS_EFFECTS_COLOR_REDUCE_EFFECT_H

#include "../material/Material.h"


class ColorReduceEffect : public Material {
public:
    explicit ColorReduceEffect(float levels);
};

#endif //DGF_GRAPHICS_EFFECTS_COLOR_REDUCE_EFFECT_H
